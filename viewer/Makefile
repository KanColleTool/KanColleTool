CP = cp
CAT = cat
ZIP = zip

SOURCES = index.html
PRODUCT = kctviewer

# On Linux and Mac (Darwin), build platform-specific binaries along with the
# .nw file. If not on either of those, PS_PRODUCT (PS = Platform Specific)
# will be empty, which will make the 'all' target build only the .nw file.
PLATFORM = $(shell uname -s)
ifeq ($(PLATFORM),Linux)
	PS_PRODUCT = $(PRODUCT)
endif
ifeq ($(PLATFORM),Darwin)
	PS_PRODUCT = $(PRODUCT).app
endif

all: $(PRODUCT).nw $(PS_PRODUCT)

clean:
	rm -rf $(PRODUCT) $(PRODUCT).nw $(PS_PRODUCT) nw.pak

$(PRODUCT): $(PRODUCT).nw nw.pak
	$(CAT) $(shell which nw) $@.nw > $@ && chmod +x $@

nw.pak:
	cp /usr/lib/node-webkit/nw.pak nw.pak

$(PRODUCT).nw: $(SOURCES)
	zip -r $@ $(SOURCES)
