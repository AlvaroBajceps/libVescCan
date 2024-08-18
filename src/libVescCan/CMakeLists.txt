set(SRC
	VESC_Convert.c
	VESC_Endian.c
)

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_sources(${PROJECT_NAME} PRIVATE ${SRC})