
#if(VER_DEBUG1 == 1)
  #define DEBUG1(x) do { qDebug() << x; } while (0)

#else
  #define DEBUG1(x)
#endif

#if(VER_DEBUG2 == 1)
  #define DEBUG2(x) do { qDebug() << x; } while (0)

#else
  #define DEBUG2(x)
#endif

