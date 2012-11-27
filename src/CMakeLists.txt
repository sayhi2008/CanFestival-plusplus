INCLUDE_DIRECTORIES(${${PROJECT_NAME}_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${${PROJECT_NAME}_SOURCE_DIR}/include/unix)
INCLUDE_DIRECTORIES(${${PROJECT_NAME}_SOURCE_DIR}/include/timers_unix)



#LINK_DIRECTORIES(${${PROJECT_NAME}_SOURCE_DIR}/INSTALL/lib/)


set(SRC_SRCS
	${${PROJECT_NAME}_SOURCE_DIR}/src/dcf.c
	${${PROJECT_NAME}_SOURCE_DIR}/src/emcy.c
	${${PROJECT_NAME}_SOURCE_DIR}/src/lifegrd.c
	${${PROJECT_NAME}_SOURCE_DIR}/src/lss.c
	${${PROJECT_NAME}_SOURCE_DIR}/src/nmtMaster.c
	${${PROJECT_NAME}_SOURCE_DIR}/src/nmtSlave.c
	${${PROJECT_NAME}_SOURCE_DIR}/src/objacces.c
	${${PROJECT_NAME}_SOURCE_DIR}/src/pdo.c
	${${PROJECT_NAME}_SOURCE_DIR}/src/sdo.c
	${${PROJECT_NAME}_SOURCE_DIR}/src/states.c
	#${${PROJECT_NAME}_SOURCE_DIR}/src/symbols.c
	${${PROJECT_NAME}_SOURCE_DIR}/src/sync.c
	${${PROJECT_NAME}_SOURCE_DIR}/src/timer.c
	#${${PROJECT_NAME}_SOURCE_DIR}/src/unix.c
	${${PROJECT_NAME}_SOURCE_DIR}/src/CfLib.cpp
	${${PROJECT_NAME}_SOURCE_DIR}/src/CfNode.cpp
	${${PROJECT_NAME}_SOURCE_DIR}/src/CfNode_401.cpp
	${${PROJECT_NAME}_SOURCE_DIR}/src/CfSystem.cpp
	${${PROJECT_NAME}_SOURCE_DIR}/src/CfResult.cpp
	${${PROJECT_NAME}_SOURCE_DIR}/src/HostNode.c
)

set(LIBCF_INCS
	${${PROJECT_NAME}_SOURCE_DIR}/include/CanFestival.h
	${${PROJECT_NAME}_SOURCE_DIR}/include/CfLib.h
	${${PROJECT_NAME}_SOURCE_DIR}/include/CfNode.h
	${${PROJECT_NAME}_SOURCE_DIR}/include/CfNode_401.h
	${${PROJECT_NAME}_SOURCE_DIR}/include/CfResult.h
	${${PROJECT_NAME}_SOURCE_DIR}/include/CfSystem.h
	${${PROJECT_NAME}_SOURCE_DIR}/include/HostNode.h
	${${PROJECT_NAME}_SOURCE_DIR}/include/unix/applicfg.h
	${${PROJECT_NAME}_SOURCE_DIR}/include/can.h
	${${PROJECT_NAME}_SOURCE_DIR}/include/can_driver.h
	${${PROJECT_NAME}_SOURCE_DIR}/include/unix/canfestival.h
	${${PROJECT_NAME}_SOURCE_DIR}/include/config.h
	${${PROJECT_NAME}_SOURCE_DIR}/include/data.h
	${${PROJECT_NAME}_SOURCE_DIR}/include/dcf.h
	${${PROJECT_NAME}_SOURCE_DIR}/include/def.h
	${${PROJECT_NAME}_SOURCE_DIR}/include/emcy.h
	${${PROJECT_NAME}_SOURCE_DIR}/include/lifegrd.h
	${${PROJECT_NAME}_SOURCE_DIR}/include/lss.h
	${${PROJECT_NAME}_SOURCE_DIR}/include/nmtMaster.h
	${${PROJECT_NAME}_SOURCE_DIR}/include/nmtSlave.h
	${${PROJECT_NAME}_SOURCE_DIR}/include/objacces.h
	${${PROJECT_NAME}_SOURCE_DIR}/include/objdictdef.h
	${${PROJECT_NAME}_SOURCE_DIR}/include/pdo.h
	${${PROJECT_NAME}_SOURCE_DIR}/include/sdo.h
	${${PROJECT_NAME}_SOURCE_DIR}/include/states.h
	${${PROJECT_NAME}_SOURCE_DIR}/include/sync.h
	${${PROJECT_NAME}_SOURCE_DIR}/include/sysdep.h
	${${PROJECT_NAME}_SOURCE_DIR}/include/timer.h
	${${PROJECT_NAME}_SOURCE_DIR}/include/timers_unix/timerscfg.h
	${${PROJECT_NAME}_SOURCE_DIR}/include/timers_driver.h
)

set(TIMERS_SRC
	${${PROJECT_NAME}_SOURCE_DIR}/drivers/timers_unix/timers_unix.c
)

set(CAN_SRC
	${${PROJECT_NAME}_SOURCE_DIR}/drivers/can_kvaser/can_kvaser.c
)

set(LIBCF_SRCS
	${${PROJECT_NAME}_SOURCE_DIR}/drivers/unix/unix.c
	${SRC_SRCS}
	${TIMERS_SRC}
	${CAN_SRC}
)

set(SRC_LIBS
	pthread
	rt
	dl
	canlib
)

ADD_LIBRARY(canfestival SHARED ${LIBCF_SRCS})
TARGET_LINK_LIBRARIES(canfestival ${SRC_LIBS})

INSTALL(TARGETS canfestival
	#RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	#ARCHIVE DESTINATION libstatic
	)
INSTALL(FILES ${LIBCF_INCS} DESTINATION include/canfestival)

