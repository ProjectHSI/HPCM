find_package(Doxygen
             OPTIONAL_COMPONENTS dot mscgen dia)

if(DOXYGEN_FOUND)
    # Relative directory hasn't been changed when this file was included, so we need to add our directory here.
    include("HPCM-Docs/DoxygenConfig.cmake")

    doxygen_add_docs(HPCM-Docs HPCM HPCM-Docs/Markdown)
elseif(HPCM_NO_BUILD_TARGETS) # Doxygen cannot have been installed if this condition is reached.
    message(WARNING "Doxygen is not installed, yet NO_BUILD_TARGETS is enabled. This is probably not what you want, since the documentation target will not be generated. Please install Doxygen to generate the documentation target.")
endif()