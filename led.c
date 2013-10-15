#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>  
#include <stdio.h>
#include	"wsIntrn.h"
#define BLK_SIZE 10000
typedef struct BigBlock {
	char data[BLK_SIZE];
} BigBlock;

int ToggleLEDHandler(webs_t wp, char_t *urlPrefix, char_t *webDir,
	int arg, char_t *url, char_t *path, char_t *query)
{
	static unsigned char led_state = 0;
	int fd;
	volatile unsigned char *p;

	websHeader(wp);

	led_state = !led_state;	

	fd=open("/dev/mem",O_RDWR);
	p = (unsigned char *)0;
#if 0
	p = mmap((void *) 0, 4, PROT_READ+PROT_WRITE,MAP_SHARED,fd,0xfa400000);
	*p ^= 0x04; //toggle LEDs
#endif
	if (led_state)
		websWrite(wp, "<center><font size=+7>LED state: <blink><font color=\"#FF0000\">ON</font></blink></font></center> ");
	else
		websWrite(wp, "<center><font size=+7>LED state: <blink>OFF</blink></font></center> ");
	
	
	websFooter(wp);
	websDone(wp,200);
	return 0;
}

static int ClearBlock(char * RealBigBlockPtr, int l)
{
	char * p;
	for (p = RealBigBlockPtr; (p - RealBigBlockPtr) < l; p++)
		*p = 0;
	return 0;
}
static int InitBlock(char * ptr, int n)
{
	return ClearBlock(ptr, n);
}

int ErrorInHandler(webs_t wp, char_t *urlPrefix, char_t *webDir,
	int arg, char_t *url, char_t *path, char_t *query)
{
	char *p;
	int siz;

	siz = 1000000 * sizeof(BigBlock);

	p = malloc(siz);
	/* if (p) */ 
		return InitBlock(p, siz);
 
	return (0);
}


