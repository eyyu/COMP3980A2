#ifndef GPSPRINT_H
#define GPSPRINT_H

#include <libgpsmm.h> 
#include <type_traits>

void printData(gps_data_t *gpsData);
void printToConsole(gps_data_t *gpsData);

/*--------------------------------------------------------------------------
-- FUNCTION TEMPLATE: hasSkyview
--
-- DATE: OCT. 14, 2016
--
-- REVISIONS: Set Version 2.0
--
-- DESIGNER: Eva Yu
--
-- PROGRAMMER: Eva Yu
--
-- INTERFACE: [returntype] [fucntionName] (functionParams)
-- [functionParam0] [description]
-- [functionParam1] [description]
-- [functionParam2] [description]
--
-- RETURNS: 
--
-- NOTES:
-- 
--------------------------------------------------------------------------*/
// template < typename T, typename = void > 
// struct hasSkyview 
// 	: std::false_type { };


// template < typename T >
// struct hasSkyview < T, decltype(std::declval<T>().skyview, void() )> 
// 	: std::true_type  { };

#endif

// DEFINE
#define DEFINE_MEMBER_CHECKER(member) \
    template<typename T, typename V = bool> \
    struct has_ ## member : false_type { }; \
    template<typename T> \
    struct has_ ## member<T, \
        typename enable_if< \
            !is_same<decltype(declval<T>().member), void>::value, \
            bool \
            >::type \
        > : true_type { };

#define HAS_MEMBER(C, member) \
    has_ ## member<C>::value

