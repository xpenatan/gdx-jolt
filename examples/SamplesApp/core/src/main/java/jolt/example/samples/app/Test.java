package jolt.example.samples.app;

import jolt.DebugRendererEm;
import jolt.jolt.core.TempAllocator;
import jolt.jolt.physics.PhysicsSystem;
import jolt.jolt.physics.body.BodyInterface;

public abstract class Test {

    PhysicsSystem mPhysicsSystem = null;
    BodyInterface mBodyInterface = null;
    DebugRendererEm mDebugRenderer = null;
    TempAllocator mTempAllocator = null;

}
