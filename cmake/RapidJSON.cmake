check_include_file_cxx(rapidjson/rapidjson.h HAVE_RAPIDJSON_RAPIDJSON_H)
if(NOT HAVE_RAPIDJSON_RAPIDJSON_H)
    error("Need to have RapidJSON installed")
endif()
