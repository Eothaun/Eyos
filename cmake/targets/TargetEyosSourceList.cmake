target_sources_local(Eyos
    PRIVATE
    eyos/Main.cpp
    #rendering
    eyos/rendering/EyosRenderer.cpp
    eyos/rendering/DebugRenderer.cpp
    eyos/rendering/UIRenderer.cpp
    eyos/rendering/VertexLayouts.cpp
    eyos/rendering/Camera.cpp
    eyos/rendering/RenderableTerrain.cpp
    # others
    eyos/Application.cpp
    eyos/Input.cpp
)