# Copyright 1999-2012 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v2
# $Header: $

EAPI=4

inherit git-2

DESCRIPTION=""
HOMEPAGE=""
SRC_URI=""

LICENSE="BeerBSD"
SLOT="0"
KEYWORDS="~amd64"
IUSE=""

DEPEND="net-libs/gloox
		>=dev-lang/lua-5.1.0
		dev-libs/openssl"

RDEPEND="${DEPEND}"

EGIT_REPO_URI="git://github.com/roa/dramaqueen.git"

src_compile() {
	make release || die "Something went terribly wrong..."
}

src_install() {
    dodir "/usr/local/bin/"
	cp "${PORTAGE_BUILDDIR}/work/dramaqueen-0.01/bin/Release/dramaqueen" \
	"${D}/usr/local/bin/" || die
	
	dodir "/etc/dramaqueen"
	cp "${PORTAGE_BUILDDIR}/work/dramaqueen-0.01/config/init.lua" \
	"${D}/etc/dramaqueen" || die

	doinitd "${FILESDIR}"/init.d/dramaqueen
}
