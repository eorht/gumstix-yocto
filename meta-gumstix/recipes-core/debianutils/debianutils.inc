DESCRIPTION = "Miscellaneous utilities specific to Debian"
SECTION = "base"
LICENSE = "GPL BSD SMAIL"
LIC_FILES_CHKSUM = "file://debian/copyright;md5=f01a5203d50512fc4830b4332b696a9f"
INC_PR = "r2"

SRC_URI = "${DEBIAN_MIRROR}/main/d/${PN}/${PN}_${PV}.tar.gz"

inherit autotools

do_install_append() {
    for app in ${D}${sbindir}/* ${D}${bindir}/*; do
        mv $app $app.${PN}
    done
    if [ "${base_bindir}" != "${bindir}" ]; then
        # Debian places some utils into ${base_bindir} as does busybox
        install -d ${D}${base_bindir}
        for app in run-parts.${PN} tempfile.${PN}; do
            mv ${D}${bindir}/$app ${D}${base_bindir}/$app
        done
    fi
}

pkg_prerm_${PN} () {
for app in add-shell  installkernel  mkboot  remove-shell run-parts  savelog  sensible-browser  sensible-editor  sensible-pager  tempfile  which ; do
   update-alternatives --remove $app $app.${PN}
done
}
pkg_postinst_${PN} () {
#!/bin/sh
for app in add-shell  installkernel  mkboot  remove-shell ; do
    update-alternatives --install ${sbindir}/$app $app $app.${PN} 100
done
for app in savelog  sensible-browser  sensible-editor  sensible-pager  which ; do
    update-alternatives --install ${bindir}/$app $app $app.${PN} 100
done
for app in run-parts  tempfile ; do
    update-alternatives --install ${base_bindir}/$app $app $app.${PN} 100
done
}
