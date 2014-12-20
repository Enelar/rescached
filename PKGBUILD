# Maintainer: sulhan <ms@kilabit.info>
_pkgname=rescached
pkgname=rescached-git
pkgver=20141219
pkgrel=1
pkgdesc="Resolver/DNS cache daemon"
arch=('i686' 'x86_64')
url="https://github.com/shuLhan/rescached"
license=('custom:BSD')
makedepends=('git' 'asciidoc')
source=("$_pkgname::git+https://github.com/shuLhan/rescached.git"
	"libvos::git+https://github.com/shuLhan/libvos.git")
sha1sums=('SKIP' 'SKIP')

pkgver() {
	cd "$srcdir/$_pkgname/src"
	printf "r%s.%s" "$(git rev-list --count HEAD)" "$(git rev-parse --short HEAD)"
}

prepare() {
	cd "$srcdir/$_pkgname/src"
	git submodule init
	git config submodule.libvos.url $srcdir/$_pkgname/src/lib
	git submodule update
}

build() {
	cd "$srcdir/$_pkgname/src"
	echo ">>"
	echo ">> cleaning ..."
	echo ">>"
	make distclean
	echo ">>"
	echo ">> make ..."
	echo ">>"
	unset CXXFLAGS
	make || return 1
}

package() {
	cd "$srcdir/$_pkgname/src"

	make DESTDIR="$pkgdir/" install
}
