# Models
belka.path     = $$OUT_PWD/bin/res/models/belka
belka.files    = $$PWD/libs/ObjectViewerLibrary/res/models/belka/*

cube.path      = $$OUT_PWD/bin/res/models/cube
cube.files     = $$PWD/libs/ObjectViewerLibrary/res/models/cube/*

suzanne.path   = $$OUT_PWD/bin/res/models
suzanne.files  = $$PWD/libs/ObjectViewerLibrary/res/models/suzanne.*

INSTALLS +=  \
    belka \
    cube \
    suzanne

# Textures
brick.path      = $$OUT_PWD/bin/res/textures
brick.files     = $$PWD/libs/ObjectViewerLibrary/res/textures/test_brick.jpg

skybox1.path    = $$OUT_PWD/bin/res/textures/skybox/cube_six_textures
skybox1.files   = $$PWD/libs/ObjectViewerLibrary/res/textures/skybox/cube_six_textures/*

skybox2.path    = $$OUT_PWD/bin/res/textures/skybox_one_file
skybox2.files   = $$PWD/libs/ObjectViewerLibrary/res/textures/skybox_one_file/*

INSTALLS += \
    brick   \
    skybox1 \
    skybox2
