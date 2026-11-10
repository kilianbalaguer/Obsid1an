SDK       = iphoneos
CC        = xcrun -sdk $(SDK) clang
CFLAGS    = -arch arm64 -miphoneos-version-min=7.0 -O2 -Wall
LDFLAGS   = -framework CoreFoundation -framework IOKit
SRC       = src/shardfetch.c
BIN       = build/shardfetch
VERSION   = 1.0.0

.PHONY: all clean deb-rootful deb-rootless deb-roothide debs

all: $(BIN)

$(BIN): $(SRC)
	@mkdir -p build
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<
	@echo "Built $(BIN)"

# ad-hoc sign for sideloaded / jailbroken use
sign: $(BIN)
	ldid -S $(BIN) 2>/dev/null || codesign -s - $(BIN) 2>/dev/null || true

deb-rootful: $(BIN)
	@rm -rf build/deb-rootful
	@mkdir -p build/deb-rootful/usr/bin
	@mkdir -p build/deb-rootful/DEBIAN
	@cp $(BIN) build/deb-rootful/usr/bin/shardfetch
	@cp packaging/rootful/DEBIAN/control build/deb-rootful/DEBIAN/
	@sed -i '' 's/VERSION_PLACEHOLDER/$(VERSION)/' build/deb-rootful/DEBIAN/control
	dpkg-deb -Zxz --root-owner-group -b build/deb-rootful build/com.obsid1an.shardfetch_$(VERSION)_rootful.deb
	@echo "Built rootful .deb"

deb-rootless: $(BIN)
	@rm -rf build/deb-rootless
	@mkdir -p build/deb-rootless/usr/bin
	@mkdir -p build/deb-rootless/DEBIAN
	@cp $(BIN) build/deb-rootless/usr/bin/shardfetch
	@cp packaging/rootless/DEBIAN/control build/deb-rootless/DEBIAN/
	@sed -i '' 's/VERSION_PLACEHOLDER/$(VERSION)/' build/deb-rootless/DEBIAN/control
	dpkg-deb -Zxz --root-owner-group -b build/deb-rootless build/com.obsid1an.shardfetch_$(VERSION)_rootless.deb
	@echo "Built rootless .deb"

deb-roothide: $(BIN)
	@rm -rf build/deb-roothide
	@mkdir -p build/deb-roothide/usr/bin
	@mkdir -p build/deb-roothide/DEBIAN
	@cp $(BIN) build/deb-roothide/usr/bin/shardfetch
	@cp packaging/roothide/DEBIAN/control build/deb-roothide/DEBIAN/
	@sed -i '' 's/VERSION_PLACEHOLDER/$(VERSION)/' build/deb-roothide/DEBIAN/control
	dpkg-deb -Zxz --root-owner-group -b build/deb-roothide build/com.obsid1an.shardfetch_$(VERSION)_roothide.deb
	@echo "Built roothide .deb"

debs: deb-rootful deb-rootless deb-roothide

clean:
	rm -rf build
