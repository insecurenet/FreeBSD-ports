# $FreeBSD$
#
# handle dependency on the makeinfo port
#
# Feature:	makeinfo
# Usage:	USES=makeinfo
# Valid ARGS:	none
#
# MAINTAINER: portmgr@FreeBSD.org

.if !defined(_INCLUDE_USES_MAKEINFO_MK)
_INCLUDE_USES_MAKEINFO_MK=	yes

.if !empty(makeinfo_ARGS)
IGNORE=	USES=makeinfo - expects no arguments
.endif

.if exists(/usr/bin/makeinfo)
MAKEINFO?=	/usr/bin/makeinfo
.else
BUILD_DEPENDS+=	makeinfo:print/texinfo
MAKEINFO?=	${LOCALBASE}/bin/makeinfo
.endif

.endif
