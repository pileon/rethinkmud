find_package(PkgConfig)

pkg_check_modules(PC_ICU REQUIRED
        icu-i18n)

if(NOT PC_ICU_FOUND)
    message(FATAL "RethinkMUD depends on the ICU library (http://site.icu-project.org/)")
endif()

set(LIBICU_LIBRARIES ${PC_ICU_LIBRARIES})
