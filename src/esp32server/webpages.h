#ifndef webpages_h
#define webpages_h

extern WebServer server;
extern volatile int nowmode;
void webRoot(void);
void webMode(void);
void web404(void);

#endif
