# Function to filter out files in the directory
function(FilterDirectoryFromGiven INPUT_LIST DIRECTORY OUTPUT_LIST)
    set(FILTERED_LIST "")

    foreach(FILE ${${INPUT_LIST}})
        string(FIND ${FILE} "/${DIRECTORY}/" EXCLUDE)
        if(EXCLUDE EQUAL -1)
            list(APPEND FILTERED_LIST ${FILE})
        endif()
    endforeach()

    # Set the output variable so it can be used outside the function
    set(${OUTPUT_LIST} ${FILTERED_LIST} PARENT_SCOPE)
endfunction()

# Filters out file extensions
function(FilterExtentions INPUT_LIST EXTENSION OUTPUT_LIST)
    set(FILTERED_LIST "")

    foreach(FILE ${${INPUT_LIST}})
        string(FIND ${FILE} "*.${EXTENSION}" EXCLUDE)
        if(EXCLUDE EQUAL -1)
            list(APPEND FILTERED_LIST ${FILE})
        endif()
    endforeach()

    # Set the output variable so it can be used outside the function
    set(${OUTPUT_LIST} ${FILTERED_LIST} PARENT_SCOPE)
endfunction()