ign_gui_add_plugin(Grid3D
  SOURCES
    Grid3D.cc
  QT_HEADERS
    Grid3D.hh
  TEST_SOURCES
    # Grid3D_TEST.cc
  PUBLIC_LINK_LIBS
   ${IGNITION-RENDERING_LIBRARIES}
)

