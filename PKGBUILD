pkgname=st-mcaimi-git
_pkgname=st
pkgver=41e4884
pkgrel=1
pkgdesc='My personal fork of Suckless Simple Terminal'
arch=('i686' 'x86_64' 'armv7h')
license=('MIT')
depends=(libxft)
makedepends=('ncurses' 'libxext' 'git')
provides=(st)
conflicts=(st)
url=https://github.com/mcaimi/st.git
source=(git+https://github.com/mcaimi/st.git)
sha256sums=(SKIP)

pkgver() {
  cd ${srcdir}/${_pkgname}
  git rev-parse --short HEAD
}

build() {
  cd ${srcdir}/${_pkgname}
  make X11INC=/usr/include/X11 X11LIB=/usr/lib/X11
}

package() {
  cd ${srcdir}/${_pkgname}
  local installopts='--mode 0644 -D --target-directory'
  local shrdir="$pkgdir/usr/share"
  local licdir="$shrdir/licenses/$pkgname"
  local docdir="$shrdir/doc/$pkgname"
  local sourcedir=${srcdir}/${_pkgname}
  make PREFIX=/usr DESTDIR="$pkgdir" install
  install $installopts "$licdir" "$sourcedir/LICENSE"
  install $installopts "$docdir" "$sourcedir/README.md"
  install $installopts "$docdir" "$sourcedir/Xresources.template"
  install $installopts "$shrdir/$pkgname" "$sourcedir/st.info"
}
