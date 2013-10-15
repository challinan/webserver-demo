objs = $(patsubst %.c,%.o,$(wildcard *.c))

# CFLAGS += -DLINUX -DOS=LINUX -DWEBS -DUEMF -DUSER_MANAGEMENT_SUPPORT -DDIGEST_ACCESS_SUPPORT
INSTALL=install

override CFLAGS += -I./include

all: webs

webs: $(objs) 
	$(CC) $(LDFLAGS) -o webs $(objs)

.PHONY: install
install: installbin installdata

.PHONY: installbin
installbin: webs
	mkdir -p $(DESTDIR)$(bindir)
	$(INSTALL) webs $(DESTDIR)$(bindir)
#	$(STRIP) $(DESTDIR)$(bindir)/webs
	chmod 755 $(DESTDIR)$(bindir)/webs

.PHONY: installdata
	echo "Install the data files here"

clean:
	rm -f *.o webs
