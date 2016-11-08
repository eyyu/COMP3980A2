struct gps_data_t {
 gps_mask_t set; /* has field been set since this was last cleared? */
 #define ONLINE_SET  (1llu<<1)
 #define TIME_SET    (1llu<<2)
 #define TIMERR_SET  (1llu<<3)
 #define LATLON_SET  (1llu<<4)
 #define ALTITUDE_SET    (1llu<<5)
 #define SPEED_SET   (1llu<<6)
 #define TRACK_SET   (1llu<<7)
 #define CLIMB_SET   (1llu<<8)
 #define STATUS_SET  (1llu<<9)
 #define MODE_SET    (1llu<<10)
 #define DOP_SET     (1llu<<11)
 #define HERR_SET    (1llu<<12)
 #define VERR_SET    (1llu<<13)
 #define ATTITUDE_SET    (1llu<<14)
 #define SATELLITE_SET   (1llu<<15)
 #define SPEEDERR_SET    (1llu<<16)
 #define TRACKERR_SET    (1llu<<17)
 #define CLIMBERR_SET    (1llu<<18)
 #define DEVICE_SET  (1llu<<19)
 #define DEVICELIST_SET  (1llu<<20)
 #define DEVICEID_SET    (1llu<<21)
 #define RTCM2_SET   (1llu<<22)
 #define RTCM3_SET   (1llu<<23)
 #define AIS_SET     (1llu<<24)
 #define PACKET_SET  (1llu<<25)
 #define SUBFRAME_SET    (1llu<<26)
 #define GST_SET     (1llu<<27)
 #define VERSION_SET (1llu<<28)
 #define POLICY_SET  (1llu<<29)
 #define LOGMESSAGE_SET  (1llu<<30)
 #define ERROR_SET   (1llu<<31)
 #define TOFF_SET    (1llu<<32)  /* not yet used */
 #define PPS_SET     (1llu<<33)
 #define NAVDATA_SET     (1llu<<34)
 #define SET_HIGH_BIT    35
     timestamp_t online;     /* NZ if GPS is on line, 0 if not.
                  *
                  * Note: gpsd clears this time when sentences
                  * fail to show up within the GPS's normal
                  * send cycle time. If the host-to-GPS
                  * link is lossy enough to drop entire
                  * sentences, this field will be
                  * prone to false zero values.
                  */
 
 #ifndef USE_QT
     socket_t gps_fd;        /* socket or file descriptor to GPS */
 #else
     void* gps_fd;
 #endif
     struct gps_fix_t    fix;    /* accumulated PVT data */
 
     /* this should move to the per-driver structure */
     double separation;      /* Geoidal separation, MSL - WGS84 (Meters) */
 
     /* GPS status -- always valid */
     int    status;      /* Do we have a fix? */
 #define STATUS_NO_FIX   0   /* no */
 #define STATUS_FIX  1   /* yes */
 
      /* precision of fix -- valid if satellites_used > 0 */
      int satellites_used;    /* Number of satellites used in solution */
      struct dop_t dop;
  
      /* redundant with the estimate elements in the fix structure */
      double epe;  /* spherical position error, 95% confidence (meters)  */
  
      /* satellite status -- valid when satellites_visible > 0 */
      timestamp_t skyview_time;   /* skyview timestamp */
      int satellites_visible; /* # of satellites in view */
      struct satellite_t skyview[MAXCHANNELS];
  
      struct devconfig_t dev; /* device that shipped last update */
  
      struct policy_t policy; /* our listening policy */
  
      struct {
      timestamp_t time;
      int ndevices;
      struct devconfig_t list[MAXUSERDEVS];
 } devices;
  
      /* pack things never reported together to reduce structure size */
  #define UNION_SET   (RTCM2_SET|RTCM3_SET|SUBFRAME_SET|AIS_SET|ATTITUDE_SET|GST_SET|VERSION_SET|LOGMESSAGE_SET|ERROR_SET|TOFF_SET|PPS_SET)
      union {
      /* unusual forms of sensor data that might come up the pipe */
      struct rtcm2_t  rtcm2;
      struct rtcm3_t  rtcm3;
      struct subframe_t subframe;
      struct ais_t ais;
      struct attitude_t attitude;
          struct navdata_t navdata;
      struct rawdata_t raw;
      struct gst_t gst;
      /* "artificial" structures for various protocol responses */
      struct version_t version;
      char error[256];
      struct timedelta_t toff;
      struct timedelta_t pps;
      };
      /* FIXME! next lib rev need to add a place to put PPS precision */
  
      /* Private data - client code must not set this */
      void *privdata;
  };

struct gps_fix_t {
  timestamp_t time;   /* Time of update */
  int    mode;    /* Mode of fix */
  #define MODE_NOT_SEEN   0   /* mode update not seen yet */
  #define MODE_NO_FIX     1   /* none */
  #define MODE_2D         2   /* good for latitude/longitude */
  #define MODE_3D         3   /* good for altitude/climb too */
  double ept;     /* Expected time uncertainty */
  double latitude;    /* Latitude in degrees (valid if mode >= 2) */
  double epy;     /* Latitude position uncertainty, meters */
  double longitude;   /* Longitude in degrees (valid if mode >= 2) */
  double epx;     /* Longitude position uncertainty, meters */
  double altitude;    /* Altitude in meters (valid if mode == 3) */
  double epv;     /* Vertical position uncertainty, meters */
  double track;   /* Course made good (relative to true north) */
  double epd;     /* Track uncertainty, degrees */
  double speed;   /* Speed over ground, meters/sec */
  double eps;     /* Speed uncertainty, meters/sec */
  double climb;       /* Vertical speed, meters/sec */
  double epc;     /* Vertical speed uncertainty */
};