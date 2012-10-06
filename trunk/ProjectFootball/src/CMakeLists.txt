#add definitions, compiler switches, etc.
ADD_DEFINITIONS(-g -ggdb -Wall -Wextra -pedantic ${CMAKE_CXX_FLAGS})

#get all source files and data files.
FILE(GLOB_RECURSE SOURCE_FILES "*.cpp")

SET(EXEC_NAME project_football)

#list all source files here
ADD_EXECUTABLE(${EXEC_NAME} ${SOURCE_FILES})

#need to link to some other libraries
TARGET_LINK_LIBRARIES(${EXEC_NAME}
		      ${Boost_LIBRARIES}
		      ${LUA_LIBRARIES}
		      ${SQLITE_LIBRARIES}
		      ${OGRE_LIBRARIES}
		      ${OIS_LIBRARIES}
		      ${CEGUI_LIBRARIES}
		      ${SDLMIXER_LIBRARY})

#add an install target here
INSTALL(TARGETS ${EXEC_NAME} RUNTIME DESTINATION ${BIN_INSTALL_PATH})

#install data files
INSTALL(DIRECTORY ${PROJECT_SOURCE_DIR}/data DESTINATION ${DATA_INSTALL_PATH} FILES_MATCHING PATTERN "*.*" PATTERN ".svn" EXCLUDE)
