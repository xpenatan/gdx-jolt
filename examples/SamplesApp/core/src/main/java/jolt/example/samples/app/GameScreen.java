package jolt.example.samples.app;

import com.badlogic.gdx.ScreenAdapter;
import com.badlogic.gdx.math.MathUtils;
import com.badlogic.gdx.utils.ScreenUtils;
import jolt.JoltInterface;
import jolt.JoltSettings;
import jolt.MeshShapeSettings;
import jolt.PhysicsMaterialList;
import jolt.RVec3;
import jolt.ShapeResult;
import jolt.TriangleList;
import jolt.jolt.geometry.Triangle;
import jolt.jolt.math.Quat;
import jolt.jolt.physics.PhysicsSystem;
import jolt.jolt.physics.body.Body;
import jolt.jolt.physics.body.BodyCreationSettings;
import jolt.jolt.physics.body.BodyInterface;
import jolt.jolt.physics.collision.ObjectLayerPairFilterTable;
import jolt.jolt.physics.collision.broadphase.BroadPhaseLayer;
import jolt.jolt.physics.collision.broadphase.BroadPhaseLayerInterfaceTable;
import jolt.jolt.physics.collision.broadphase.ObjectVsBroadPhaseLayerFilterTable;
import static jolt.EMotionType.EMotionType_Static;
import static jolt.jolt.physics.EActivation.EActivation_Activate;

public class GameScreen extends ScreenAdapter {

    // Object layers
    static int LAYER_NON_MOVING = 0;
    static int LAYER_MOVING = 1;
    static int NUM_OBJECT_LAYERS = 2;


    private JoltInterface jolt;
    private PhysicsSystem physicsSystem;
    private BodyInterface bodyInterface;

    @Override
    public void show() {
        JoltSettings settings = new JoltSettings();
        setupCollisionFiltering(settings);
        jolt = new JoltInterface(settings);
//        settings.dispose();

        physicsSystem = jolt.GetPhysicsSystem();
        bodyInterface = physicsSystem.GetBodyInterface();

        createMeshFloor(30, 1, 4, 0, 5, 0);
    }

    @Override
    public void render(float delta) {
        ScreenUtils.clear(1, 1, 1, 1, true);
        // Don't go below 30 Hz to prevent spiral of death
        float deltaTime = (float)Math.min(delta, 1.0 / 30.0);

        updatePhysics(deltaTime);
    }

    private void setupCollisionFiltering(JoltSettings settings) {
        // Layer that objects can be in, determines which other objects it can collide with
        // Typically you at least want to have 1 layer for moving bodies and 1 layer for static bodies, but you can have more
        // layers if you want. E.g. you could have a layer for high detail collision (which is not used by the physics simulation
        // but only if you do collision testing).

        ObjectLayerPairFilterTable objectFilter = new ObjectLayerPairFilterTable(NUM_OBJECT_LAYERS);
        objectFilter.EnableCollision(LAYER_NON_MOVING, LAYER_MOVING);
        objectFilter.EnableCollision(LAYER_MOVING, LAYER_MOVING);

        // Each broadphase layer results in a separate bounding volume tree in the broad phase. You at least want to have
        // a layer for non-moving and moving objects to avoid having to update a tree full of static objects every frame.
        // You can have a 1-on-1 mapping between object layers and broadphase layers (like in this case) but if you have
        // many object layers you'll be creating many broad phase trees, which is not efficient.

        BroadPhaseLayer BP_LAYER_NON_MOVING = new BroadPhaseLayer((short)0);
        BroadPhaseLayer BP_LAYER_MOVING = new BroadPhaseLayer((short)1);
        int NUM_BROAD_PHASE_LAYERS = 2;
        BroadPhaseLayerInterfaceTable bpInterface = new BroadPhaseLayerInterfaceTable(NUM_OBJECT_LAYERS, NUM_BROAD_PHASE_LAYERS);
        bpInterface.MapObjectToBroadPhaseLayer(LAYER_NON_MOVING, BP_LAYER_NON_MOVING);
        bpInterface.MapObjectToBroadPhaseLayer(LAYER_MOVING, BP_LAYER_MOVING);

        settings.set_mObjectLayerPairFilter(objectFilter);
        settings.set_mBroadPhaseLayerInterface(bpInterface);
        ObjectVsBroadPhaseLayerFilterTable broadPhaseLayerFilter = new ObjectVsBroadPhaseLayerFilterTable(settings.get_mBroadPhaseLayerInterface(), NUM_BROAD_PHASE_LAYERS, settings.get_mObjectLayerPairFilter(), NUM_OBJECT_LAYERS);
        settings.set_mObjectVsBroadPhaseLayerFilter(broadPhaseLayerFilter);
    }

    private void updatePhysics(float deltaTime) {
        // When running below 55 Hz, do 2 steps instead of 1
        var numSteps = deltaTime > 1.0 / 55.0 ? 2 : 1;
        jolt.Step(deltaTime, numSteps);
    }

    private float height(float x, float y) {
        return MathUtils.sin(x / 2) * MathUtils.cos(y / 3);
    }

    private void createMeshFloor(int n,  int cellSize, int maxHeight, float posX, float posY, float posZ) {
        // Create regular grid of triangles

        TriangleList triangles = new TriangleList();
        triangles.resize(n * n * 2);
        for (int x = 0; x < n; ++x)
            for (int z = 0; z < n; ++z) {
                float center = n * cellSize / 2.0f;

                float x1 = cellSize * x - center;
                float z1 = cellSize * z - center;
                float x2 = x1 + cellSize;
                float z2 = z1 + cellSize;

                {
                    Triangle t = triangles.at((x * n + z) * 2);
                    var v1 = t.get_mV(0);
                    v1.set_x(x1);
                    v1.set_y(height(x, z));
                    v1.set_z(z1);
                    var v2 = t.get_mV(1);
                    v2.set_x(x1);
                    v2.set_y(height(x, z + 1));
                    v2.set_z(z2);
                    var v3 = t.get_mV(2);
                    v3.set_x(x2);
                    v3.set_y(height(x + 1, z + 1));
                    v3.set_z(z2);
                }

                {
                    var t = triangles.at((x * n + z) * 2 + 1);
                    var v1 = t.get_mV(0);
                    v1.set_x(x1);
                    v1.set_y(height(x, z));
                    v1.set_z(z1);
                    var v2 = t.get_mV(1);
                    v2.set_x(x2);
                    v2.set_y(height(x + 1, z + 1));
                    v2.set_z(z2);
                    var v3 = t.get_mV(2);
                    v3.set_x(x2);
                    v3.set_y(height(x + 1, z));
                    v3.set_z(z1);
                }
            }
        var materials = new PhysicsMaterialList();
        ShapeResult shapeResult = new MeshShapeSettings(triangles, materials).Create();
        triangles.dispose();
        materials.dispose();
        boolean hasError = shapeResult.HasError();
        boolean isValid = shapeResult.IsValid();
        System.out.println("ShapeResult hasError: " + hasError);
        System.out.println("ShapeResult isValid: " + isValid);
//        IDLString idlString = shapeResult.GetError();
//        long cPointer = idlString.getCPointer();
//        String data = idlString.data();
//        System.out.println("ShapeResult GetError: " + data);
        var shape = shapeResult.Get();
        // Create body
        var creationSettings = new BodyCreationSettings(shape, new RVec3(posX, posY, posZ), new Quat(0, 0, 0, 1), EMotionType_Static, LAYER_NON_MOVING);
        var body = bodyInterface.CreateBody(creationSettings);
        creationSettings.dispose();
        addToScene(body, 0xc7c7c7);
    }

    void addToScene(Body body, int color) {
        bodyInterface.AddBody(body.GetID(), EActivation_Activate);

//        addToThreeScene(body, color);
    }

}