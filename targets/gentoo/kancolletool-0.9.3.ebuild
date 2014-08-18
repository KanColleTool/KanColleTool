# Copyright 1999-2014 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v2
# $Header: $

EAPI=5

inherit eutils cmake-utils git-r3

DESCRIPTION="Makes KanColle better"
HOMEPAGE="http://kancolletool.github.io"
LICENSE="MIT"

EGIT_REPO_URI="https://github.com/KanColleTool/KanColleTool.git"

SLOT="0"
KEYWORDS="~x86 ~amd64"
IUSE=""

# A space delimited list of portage features to restrict. man 5 ebuild
# for details.  Usually not needed.
#RESTRICT="strip"

DEPEND="dev-qt/qtcore:5
	dev-qt/qtwidgets:5
	dev-qt/qtwebkit:5[widgets]
	dev-qt/qttest:5"
RDEPEND="${DEPEND}
	 www-plugins/adobe-flash"

# Source directory; the dir where the sources can be found (automatically
# unpacked) inside ${WORKDIR}.  The default value for S is ${WORKDIR}/${P}
# If you don't need to change it, leave the S= line out of the ebuild
# to keep it tidy.
S=${WORKDIR}/${P}

src_install() {
	cmake-utils_src_install || die "Install filed"

	domenu ${S}/tool/resources/kancolletool.desktop ${S}/viewer/resources/kancolletool-viewer.desktop
	doicon -s 192 ${S}/tool/resources/kancolletool.png ${S}/viewer/resources/kancolletool-viewer.png
}
