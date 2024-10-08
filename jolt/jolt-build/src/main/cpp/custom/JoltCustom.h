#pragma once

#include "Jolt/Jolt.h"
#include "Jolt/RegisterTypes.h"
#include "Jolt/Core/Factory.h"
#include "Jolt/Core/JobSystemThreadPool.h"
#include "Jolt/Math/Vec3.h"
#include "Jolt/Math/Quat.h"
#include "Jolt/Geometry/OrientedBox.h"
#include "Jolt/Physics/PhysicsSystem.h"
#include "Jolt/Physics/StateRecorderImpl.h"
#include "Jolt/Physics/Collision/RayCast.h"
#include "Jolt/Physics/Collision/CastResult.h"
#include "Jolt/Physics/Collision/AABoxCast.h"
#include "Jolt/Physics/Collision/ShapeCast.h"
#include "Jolt/Physics/Collision/CollidePointResult.h"
#include "Jolt/Physics/Collision/Shape/SphereShape.h"
#include "Jolt/Physics/Collision/Shape/BoxShape.h"
#include "Jolt/Physics/Collision/Shape/CapsuleShape.h"
#include "Jolt/Physics/Collision/Shape/TaperedCapsuleShape.h"
#include "Jolt/Physics/Collision/Shape/CylinderShape.h"
#include "Jolt/Physics/Collision/Shape/ConvexHullShape.h"
#include "Jolt/Physics/Collision/Shape/StaticCompoundShape.h"
#include "Jolt/Physics/Collision/Shape/MutableCompoundShape.h"
#include "Jolt/Physics/Collision/Shape/ScaledShape.h"
#include "Jolt/Physics/Collision/Shape/OffsetCenterOfMassShape.h"
#include "Jolt/Physics/Collision/Shape/RotatedTranslatedShape.h"
#include "Jolt/Physics/Collision/Shape/MeshShape.h"
#include "Jolt/Physics/Collision/Shape/HeightFieldShape.h"
#include "Jolt/Physics/Collision/CollisionCollectorImpl.h"
#include "Jolt/Physics/Collision/GroupFilterTable.h"
#include "Jolt/Physics/Collision/CollideShape.h"
#include "Jolt/Physics/Constraints/FixedConstraint.h"
#include "Jolt/Physics/Constraints/PointConstraint.h"
#include "Jolt/Physics/Constraints/DistanceConstraint.h"
#include "Jolt/Physics/Constraints/HingeConstraint.h"
#include "Jolt/Physics/Constraints/ConeConstraint.h"
#include "Jolt/Physics/Constraints/PathConstraint.h"
#include "Jolt/Physics/Constraints/PathConstraintPath.h"
#include "Jolt/Physics/Constraints/PulleyConstraint.h"
#include "Jolt/Physics/Constraints/SliderConstraint.h"
#include "Jolt/Physics/Constraints/SwingTwistConstraint.h"
#include "Jolt/Physics/Constraints/SixDOFConstraint.h"
#include "Jolt/Physics/Constraints/GearConstraint.h"
#include "Jolt/Physics/Constraints/RackAndPinionConstraint.h"
#include "Jolt/Physics/Body/BodyInterface.h"
#include "Jolt/Physics/Body/BodyCreationSettings.h"
#include "Jolt/Physics/Ragdoll/Ragdoll.h"
#include "Jolt/Physics/SoftBody/SoftBodyCreationSettings.h"
#include "Jolt/Physics/SoftBody/SoftBodySharedSettings.h"
#include "Jolt/Physics/SoftBody/SoftBodyShape.h"
#include "Jolt/Physics/SoftBody/SoftBodyMotionProperties.h"
#include "Jolt/Physics/SoftBody/SoftBodyContactListener.h"
#include "Jolt/Physics/SoftBody/SoftBodyManifold.h"
#include "Jolt/Physics/Character/CharacterVirtual.h"
#include "Jolt/Physics/Vehicle/VehicleConstraint.h"
#include "Jolt/Physics/Vehicle/MotorcycleController.h"
#include "Jolt/Physics/Vehicle/TrackedVehicleController.h"
#include "Jolt/Physics/Collision/BroadPhase/BroadPhaseLayerInterfaceTable.h"
#include "Jolt/Physics/Collision/BroadPhase/ObjectVsBroadPhaseLayerFilterTable.h"
#include "Jolt/Physics/Collision/ObjectLayerPairFilterTable.h"
#include "Jolt/Physics/Collision/BroadPhase/BroadPhaseLayerInterfaceMask.h"
#include "Jolt/Physics/Collision/BroadPhase/ObjectVsBroadPhaseLayerFilterMask.h"
#include "Jolt/Physics/Collision/ObjectLayerPairFilterMask.h"
#include "Jolt/Physics/Body/BodyActivationListener.h"
#include "Jolt/Skeleton/SkeletalAnimation.h"
#include "Jolt/Skeleton/SkeletonPose.h"
#include "Jolt/Skeleton/Skeleton.h"

#include <iostream>
//#include <malloc.h>
#include <stdlib.h>
//#include <unistd.h>
//#include <emscripten/em_asm.h>

using namespace JPH;
using namespace std;
//
//#ifdef JPH_DEBUG_RENDERER
//    #include "JoltJS-DebugRenderer.h"
//#endif
//
//// Ensure that we use 32-bit object layers
//static_assert(sizeof(ObjectLayer) == 4);
//
//// Types that need to be exposed to JavaScript
using ArrayVec3 = Array<Vec3>;
using ArrayFloat = Array<float>;
using ArrayUint = Array<uint>;
using ArrayUint8 = Array<uint8>;
using Vec3MemRef = Vec3;
using QuatMemRef = Quat;
using ArrayQuat = Array<Quat>;
using Mat44MemRef = Mat44;
using ArrayMat44 = Array<Mat44>;
using FloatMemRef = float;
using UintMemRef = uint;
using Uint8MemRef = uint8;
using SoftBodySharedSettingsVertex = SoftBodySharedSettings::Vertex;
using SoftBodySharedSettingsFace = SoftBodySharedSettings::Face;
using SoftBodySharedSettingsEdge = SoftBodySharedSettings::Edge;
using SoftBodySharedSettingsDihedralBend = SoftBodySharedSettings::DihedralBend;
using SoftBodySharedSettingsVolume = SoftBodySharedSettings::Volume;
using SoftBodySharedSettingsInvBind = SoftBodySharedSettings::InvBind;
using SoftBodySharedSettingsSkinWeight = SoftBodySharedSettings::SkinWeight;
using SoftBodySharedSettingsSkinned = SoftBodySharedSettings::Skinned;
using SoftBodySharedSettingsLRA = SoftBodySharedSettings::LRA;
using SoftBodySharedSettingsVertexAttributes = SoftBodySharedSettings::VertexAttributes;
using CollideShapeResultFace = CollideShapeResult::Face;
using ArraySoftBodySharedSettingsVertex = Array<SoftBodySharedSettingsVertex>;
using ArraySoftBodySharedSettingsFace = Array<SoftBodySharedSettingsFace>;
using ArraySoftBodySharedSettingsEdge = Array<SoftBodySharedSettingsEdge>;
using ArraySoftBodySharedSettingsDihedralBend = Array<SoftBodySharedSettingsDihedralBend>;
using ArraySoftBodySharedSettingsVolume = Array<SoftBodySharedSettingsVolume>;
using ArraySoftBodySharedSettingsInvBind = Array<SoftBodySharedSettingsInvBind>;
using ArraySoftBodySharedSettingsSkinWeight = Array<SoftBodySharedSettingsSkinWeight>;
using ArraySoftBodySharedSettingsSkinned = Array<SoftBodySharedSettingsSkinned>;
using ArraySoftBodySharedSettingsLRA = Array<SoftBodySharedSettingsLRA>;
using ArraySoftBodySharedSettingsVertexAttributes = Array<SoftBodySharedSettingsVertexAttributes>;
using ArraySoftBodyVertex = Array<SoftBodyVertex>;
using EGroundState = CharacterBase::EGroundState;
using Vector2 = Vector<2>;
using ArrayRayCastResult = Array<RayCastResult>;
using CastRayAllHitCollisionCollector = AllHitCollisionCollector<CastRayCollector>;
using CastRayClosestHitCollisionCollector = ClosestHitCollisionCollector<CastRayCollector>;
using CastRayAnyHitCollisionCollector = AnyHitCollisionCollector<CastRayCollector>;
using ArrayCollidePointResult = Array<CollidePointResult>;
using CollidePointAllHitCollisionCollector = AllHitCollisionCollector<CollidePointCollector>;
using CollidePointClosestHitCollisionCollector = ClosestHitCollisionCollector<CollidePointCollector>;
using CollidePointAnyHitCollisionCollector = AnyHitCollisionCollector<CollidePointCollector>;
using ArrayCollideShapeResult = Array<CollideShapeResult>;
using CollideShapeAllHitCollisionCollector = AllHitCollisionCollector<CollideShapeCollector>;
using CollideShapeClosestHitCollisionCollector = ClosestHitCollisionCollector<CollideShapeCollector>;
using CollideShapeAnyHitCollisionCollector = AnyHitCollisionCollector<CollideShapeCollector>;
using ArrayShapeCastResult = Array<ShapeCastResult>;
using CastShapeAllHitCollisionCollector = AllHitCollisionCollector<CastShapeCollector>;
using CastShapeClosestHitCollisionCollector = ClosestHitCollisionCollector<CastShapeCollector>;
using CastShapeAnyHitCollisionCollector = AnyHitCollisionCollector<CastShapeCollector>;
using ArrayWheelSettings = Array<Ref<WheelSettings>>;
using ArrayVehicleAntiRollBar = Array<VehicleAntiRollBar>;
using ArrayVehicleDifferentialSettings = Array<VehicleDifferentialSettings>;
using SkeletalAnimationJointState = SkeletalAnimation::JointState;
using SkeletalAnimationKeyframe = SkeletalAnimation::Keyframe;
using SkeletalAnimationAnimatedJoint = SkeletalAnimation::AnimatedJoint;
using ArraySkeletonKeyframe = Array<SkeletalAnimationKeyframe>;
using ArraySkeletonAnimatedJoint = Array<SkeletalAnimationAnimatedJoint>;
using RagdollPart = RagdollSettings::Part;
using RagdollAdditionalConstraint = RagdollSettings::AdditionalConstraint;
using ArrayRagdollPart = Array<RagdollPart>;
using ArrayRagdollAdditionalConstraint = Array<RagdollAdditionalConstraint>;
using CompoundShapeSubShape = CompoundShape::SubShape;

// Alias for EBodyType values to avoid clashes
constexpr EBodyType EBodyType_RigidBody = EBodyType::RigidBody;
constexpr EBodyType EBodyType_SoftBody = EBodyType::SoftBody;

// Alias for EMotionType values to avoid clashes
constexpr EMotionType EMotionType_Static = EMotionType::Static;
constexpr EMotionType EMotionType_Kinematic = EMotionType::Kinematic;
constexpr EMotionType EMotionType_Dynamic = EMotionType::Dynamic;

// Alias for EMotionQuality values to avoid clashes
constexpr EMotionQuality EMotionQuality_Discrete = EMotionQuality::Discrete;
constexpr EMotionQuality EMotionQuality_LinearCast = EMotionQuality::LinearCast;

// Alias for EActivation values to avoid clashes
constexpr EActivation EActivation_Activate = EActivation::Activate;
constexpr EActivation EActivation_DontActivate = EActivation::DontActivate;

// Alias for EShapeType values to avoid clashes
constexpr EShapeType EShapeType_Convex = EShapeType::Convex;
constexpr EShapeType EShapeType_Compound = EShapeType::Compound;
constexpr EShapeType EShapeType_Decorated = EShapeType::Decorated;
constexpr EShapeType EShapeType_Mesh = EShapeType::Mesh;
constexpr EShapeType EShapeType_HeightField = EShapeType::HeightField;

// Alias for EShapeSubType values to avoid clashes
constexpr EShapeSubType EShapeSubType_Sphere = EShapeSubType::Sphere;
constexpr EShapeSubType EShapeSubType_Box = EShapeSubType::Box;
constexpr EShapeSubType EShapeSubType_Capsule = EShapeSubType::Capsule;
constexpr EShapeSubType EShapeSubType_TaperedCapsule = EShapeSubType::TaperedCapsule;
constexpr EShapeSubType EShapeSubType_Cylinder = EShapeSubType::Cylinder;
constexpr EShapeSubType EShapeSubType_ConvexHull = EShapeSubType::ConvexHull;
constexpr EShapeSubType EShapeSubType_StaticCompound = EShapeSubType::StaticCompound;
constexpr EShapeSubType EShapeSubType_MutableCompound = EShapeSubType::MutableCompound;
constexpr EShapeSubType EShapeSubType_RotatedTranslated = EShapeSubType::RotatedTranslated;
constexpr EShapeSubType EShapeSubType_Scaled = EShapeSubType::Scaled;
constexpr EShapeSubType EShapeSubType_OffsetCenterOfMass = EShapeSubType::OffsetCenterOfMass;
constexpr EShapeSubType EShapeSubType_Mesh = EShapeSubType::Mesh;
constexpr EShapeSubType EShapeSubType_HeightField = EShapeSubType::HeightField;

// Alias for EConstraintSpace values to avoid clashes
constexpr EConstraintSpace EConstraintSpace_LocalToBodyCOM = EConstraintSpace::LocalToBodyCOM;
constexpr EConstraintSpace EConstraintSpace_WorldSpace = EConstraintSpace::WorldSpace;

// Alias for ESpringMode values to avoid clashes
constexpr ESpringMode ESpringMode_FrequencyAndDamping = ESpringMode::FrequencyAndDamping;
constexpr ESpringMode ESpringMode_StiffnessAndDamping = ESpringMode::StiffnessAndDamping;

// Alias for EOverrideMassProperties values to avoid clashes
constexpr EOverrideMassProperties EOverrideMassProperties_CalculateMassAndInertia = EOverrideMassProperties::CalculateMassAndInertia;
constexpr EOverrideMassProperties EOverrideMassProperties_CalculateInertia = EOverrideMassProperties::CalculateInertia;
constexpr EOverrideMassProperties EOverrideMassProperties_MassAndInertiaProvided = EOverrideMassProperties::MassAndInertiaProvided;

// Alias for EAllowedDOFs values to avoid clashes
constexpr EAllowedDOFs EAllowedDOFs_TranslationX = EAllowedDOFs::TranslationX;
constexpr EAllowedDOFs EAllowedDOFs_TranslationY = EAllowedDOFs::TranslationY;
constexpr EAllowedDOFs EAllowedDOFs_TranslationZ = EAllowedDOFs::TranslationZ;
constexpr EAllowedDOFs EAllowedDOFs_RotationX = EAllowedDOFs::RotationX;
constexpr EAllowedDOFs EAllowedDOFs_RotationY = EAllowedDOFs::RotationY;
constexpr EAllowedDOFs EAllowedDOFs_RotationZ = EAllowedDOFs::RotationZ;
constexpr EAllowedDOFs EAllowedDOFs_Plane2D = EAllowedDOFs::Plane2D;
constexpr EAllowedDOFs EAllowedDOFs_All = EAllowedDOFs::All;

// Alias for EStateRecorderState values to avoid clashes
constexpr EStateRecorderState EStateRecorderState_None = EStateRecorderState::None;
constexpr EStateRecorderState EStateRecorderState_Global = EStateRecorderState::Global;
constexpr EStateRecorderState EStateRecorderState_Bodies = EStateRecorderState::Bodies;
constexpr EStateRecorderState EStateRecorderState_Contacts = EStateRecorderState::Contacts;
constexpr EStateRecorderState EStateRecorderState_Constraints = EStateRecorderState::Constraints;
constexpr EStateRecorderState EStateRecorderState_All = EStateRecorderState::All;

// Alias for EBackFaceMode values to avoid clashes
constexpr EBackFaceMode EBackFaceMode_IgnoreBackFaces = EBackFaceMode::IgnoreBackFaces;
constexpr EBackFaceMode EBackFaceMode_CollideWithBackFaces = EBackFaceMode::CollideWithBackFaces;

// Alias for EGroundState values to avoid clashes
constexpr EGroundState EGroundState_OnGround = EGroundState::OnGround;
constexpr EGroundState EGroundState_OnSteepGround = EGroundState::OnSteepGround;
constexpr EGroundState EGroundState_NotSupported = EGroundState::NotSupported;
constexpr EGroundState EGroundState_InAir = EGroundState::InAir;

// Alias for ValidateResult values to avoid clashes
constexpr ValidateResult ValidateResult_AcceptAllContactsForThisBodyPair = ValidateResult::AcceptAllContactsForThisBodyPair;
constexpr ValidateResult ValidateResult_AcceptContact = ValidateResult::AcceptContact;
constexpr ValidateResult ValidateResult_RejectContact = ValidateResult::RejectContact;
constexpr ValidateResult ValidateResult_RejectAllContactsForThisBodyPair = ValidateResult::RejectAllContactsForThisBodyPair;

// Alias for SoftBodyValidateResult values to avoid clashes
constexpr SoftBodyValidateResult SoftBodyValidateResult_AcceptContact = SoftBodyValidateResult::AcceptContact;
constexpr SoftBodyValidateResult SoftBodyValidateResult_RejectContact = SoftBodyValidateResult::RejectContact;

// Alias for EActiveEdgeMode values to avoid clashes
constexpr EActiveEdgeMode EActiveEdgeMode_CollideOnlyWithActive = EActiveEdgeMode::CollideOnlyWithActive;
constexpr EActiveEdgeMode EActiveEdgeMode_CollideWithAll = EActiveEdgeMode::CollideWithAll;

// Alias for ECollectFacesMode values to avoid clashes
constexpr ECollectFacesMode ECollectFacesMode_CollectFaces = ECollectFacesMode::CollectFaces;
constexpr ECollectFacesMode ECollectFacesMode_NoFaces = ECollectFacesMode::NoFaces;

// Alias for EConstraintType values to avoid clashes
constexpr EConstraintType EConstraintType_Constraint = EConstraintType::Constraint;
constexpr EConstraintType EConstraintType_TwoBodyConstraint = EConstraintType::TwoBodyConstraint;

// Alias for EConstraintSubType values to avoid clashes
constexpr EConstraintSubType EConstraintSubType_Fixed = EConstraintSubType::Fixed;
constexpr EConstraintSubType EConstraintSubType_Point = EConstraintSubType::Point;
constexpr EConstraintSubType EConstraintSubType_Hinge = EConstraintSubType::Hinge;
constexpr EConstraintSubType EConstraintSubType_Slider = EConstraintSubType::Slider;
constexpr EConstraintSubType EConstraintSubType_Distance = EConstraintSubType::Distance;
constexpr EConstraintSubType EConstraintSubType_Cone = EConstraintSubType::Cone;
constexpr EConstraintSubType EConstraintSubType_SwingTwist = EConstraintSubType::SwingTwist;
constexpr EConstraintSubType EConstraintSubType_SixDOF = EConstraintSubType::SixDOF;
constexpr EConstraintSubType EConstraintSubType_Path = EConstraintSubType::Path;
constexpr EConstraintSubType EConstraintSubType_Vehicle = EConstraintSubType::Vehicle;
constexpr EConstraintSubType EConstraintSubType_RackAndPinion = EConstraintSubType::RackAndPinion;
constexpr EConstraintSubType EConstraintSubType_Gear = EConstraintSubType::Gear;
constexpr EConstraintSubType EConstraintSubType_Pulley = EConstraintSubType::Pulley;

/// Alias for EPathRotationConstraintType to avoid clash
constexpr EPathRotationConstraintType EPathRotationConstraintType_Free = EPathRotationConstraintType::Free;
constexpr EPathRotationConstraintType EPathRotationConstraintType_ConstrainAroundTangent = EPathRotationConstraintType::ConstrainAroundTangent;
constexpr EPathRotationConstraintType EPathRotationConstraintType_ConstrainAroundNormal = EPathRotationConstraintType::ConstrainAroundNormal;
constexpr EPathRotationConstraintType EPathRotationConstraintType_ConstrainAroundBinormal = EPathRotationConstraintType::ConstrainAroundBinormal;
constexpr EPathRotationConstraintType EPathRotationConstraintType_ConstrainToPath = EPathRotationConstraintType::ConstrainToPath;
constexpr EPathRotationConstraintType EPathRotationConstraintType_FullyConstrained = EPathRotationConstraintType::FullyConstrained;

// Alias for SixDOFConstraintSettings::EAxis to avoid clashes
using SixDOFConstraintSettings_EAxis = SixDOFConstraintSettings::EAxis;
constexpr SixDOFConstraintSettings_EAxis SixDOFConstraintSettings_EAxis_TranslationX = SixDOFConstraintSettings_EAxis::TranslationX;
constexpr SixDOFConstraintSettings_EAxis SixDOFConstraintSettings_EAxis_TranslationY = SixDOFConstraintSettings_EAxis::TranslationY;
constexpr SixDOFConstraintSettings_EAxis SixDOFConstraintSettings_EAxis_TranslationZ = SixDOFConstraintSettings_EAxis::TranslationZ;
constexpr SixDOFConstraintSettings_EAxis SixDOFConstraintSettings_EAxis_RotationX = SixDOFConstraintSettings_EAxis::RotationX;
constexpr SixDOFConstraintSettings_EAxis SixDOFConstraintSettings_EAxis_RotationY = SixDOFConstraintSettings_EAxis::RotationY;
constexpr SixDOFConstraintSettings_EAxis SixDOFConstraintSettings_EAxis_RotationZ = SixDOFConstraintSettings_EAxis::RotationZ;

// Alias for EMotorState values to avoid clashes
constexpr EMotorState EMotorState_Off = EMotorState::Off;
constexpr EMotorState EMotorState_Velocity = EMotorState::Velocity;
constexpr EMotorState EMotorState_Position = EMotorState::Position;

// Alias for ETransmissionMode values to avoid clashes
constexpr ETransmissionMode ETransmissionMode_Auto = ETransmissionMode::Auto;
constexpr ETransmissionMode ETransmissionMode_Manual = ETransmissionMode::Manual;

// Defining ETireFrictionDirection since we cannot pass references to float
enum ETireFrictionDirection
{
    ETireFrictionDirection_Longitudinal,
    ETireFrictionDirection_Lateral
};

// Alias for ESwingType values to avoid clashes
constexpr ESwingType ESwingType_Cone = ESwingType::Cone;
constexpr ESwingType ESwingType_Pyramid = ESwingType::Pyramid;

// Alias for EBendType values to avoid clashes
using SoftBodySharedSettings_EBendType = SoftBodySharedSettings::EBendType;
constexpr SoftBodySharedSettings_EBendType SoftBodySharedSettings_EBendType_None = SoftBodySharedSettings::EBendType::None;
constexpr SoftBodySharedSettings_EBendType SoftBodySharedSettings_EBendType_Distance = SoftBodySharedSettings::EBendType::Distance;
constexpr SoftBodySharedSettings_EBendType SoftBodySharedSettings_EBendType_Dihedral = SoftBodySharedSettings::EBendType::Dihedral;

// Alias for ELRAType values to avoid clashes
using SoftBodySharedSettings_ELRAType = SoftBodySharedSettings::ELRAType;
constexpr SoftBodySharedSettings_ELRAType SoftBodySharedSettings_ELRAType_None = SoftBodySharedSettings::ELRAType::None;
constexpr SoftBodySharedSettings_ELRAType SoftBodySharedSettings_ELRAType_EuclideanDistance = SoftBodySharedSettings::ELRAType::EuclideanDistance;
constexpr SoftBodySharedSettings_ELRAType SoftBodySharedSettings_ELRAType_GeodesicDistance = SoftBodySharedSettings::ELRAType::GeodesicDistance;

// Helper class to store information about the memory layout of SoftBodyVertex
class SoftBodyVertexTraits
{
public:
    static constexpr uint mPreviousPositionOffset = offsetof(SoftBodyVertex, mPreviousPosition);
    static constexpr uint mPositionOffset = offsetof(SoftBodyVertex, mPosition);
    static constexpr uint mVelocityOffset = offsetof(SoftBodyVertex, mVelocity);
};

// Callback for traces
static void TraceImpl(const char *inFMT, ...)
{
    // Format the message
    va_list list;
    va_start(list, inFMT);
    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), inFMT, list);

    // Print to the TTY
    cout << buffer << endl;
}

#ifdef JPH_ENABLE_ASSERTS

// Callback for asserts
static bool AssertFailedImpl(const char *inExpression, const char *inMessage, const char *inFile, uint inLine)
{
    // Print to the TTY
    cout << inFile << ":" << inLine << ": (" << inExpression << ") " << (inMessage != nullptr? inMessage : "") << endl;

    // Breakpoint
    return true;
};

#endif // JPH_ENABLE_ASSERTS

/// Settings to pass to constructor
class JoltSettings
{
public:
    uint mMaxBodies = 10240;
    uint mMaxBodyPairs = 65536;
    uint mMaxContactConstraints = 10240;
    uint mTempAllocatorSize = 10 * 1024 * 1024;
    BroadPhaseLayerInterface *mBroadPhaseLayerInterface = nullptr;
    ObjectVsBroadPhaseLayerFilter *mObjectVsBroadPhaseLayerFilter = nullptr;
    ObjectLayerPairFilter *	mObjectLayerPairFilter = nullptr;
};

/// Main API for JavaScript
class JoltInterface
{
public:
    /// Constructor
    JoltInterface(const JoltSettings &inSettings)
    {
        // Install callbacks
        Trace = TraceImpl;
        JPH_IF_ENABLE_ASSERTS(AssertFailed = AssertFailedImpl;)

        // Create a factory
        Factory::sInstance = new Factory();

        // Register all Jolt physics types
        RegisterTypes();

        // Init temp allocator
        mTempAllocator = new TempAllocatorImpl(inSettings.mTempAllocatorSize);

        // Check required objects
        if (inSettings.mBroadPhaseLayerInterface == nullptr || inSettings.mObjectVsBroadPhaseLayerFilter == nullptr || inSettings.mObjectLayerPairFilter == nullptr)
            Trace("Error: BroadPhaseLayerInterface, ObjectVsBroadPhaseLayerFilter and ObjectLayerPairFilter must be provided");

        // Store interfaces
        mBroadPhaseLayerInterface = inSettings.mBroadPhaseLayerInterface;
        mObjectVsBroadPhaseLayerFilter = inSettings.mObjectVsBroadPhaseLayerFilter;
        mObjectLayerPairFilter = inSettings.mObjectLayerPairFilter;

        // Init the physics system
        constexpr uint cNumBodyMutexes = 0;
        mPhysicsSystem = new PhysicsSystem();
        mPhysicsSystem->Init(inSettings.mMaxBodies, cNumBodyMutexes, inSettings.mMaxBodyPairs, inSettings.mMaxContactConstraints, *inSettings.mBroadPhaseLayerInterface, *inSettings.mObjectVsBroadPhaseLayerFilter, *inSettings.mObjectLayerPairFilter);
    }

    /// Destructor
    ~JoltInterface()
    {
        // Destroy subsystems
        delete mPhysicsSystem;
        delete mBroadPhaseLayerInterface;
        delete mObjectVsBroadPhaseLayerFilter;
        delete mObjectLayerPairFilter;
        delete mTempAllocator;
        delete Factory::sInstance;
        Factory::sInstance = nullptr;
        UnregisterTypes();
    }

    /// Step the world
    void Step(float inDeltaTime, int inCollisionSteps)
    {
        mPhysicsSystem->Update(inDeltaTime, inCollisionSteps, mTempAllocator, &mJobSystem);
    }

    /// Access to the physics system
    PhysicsSystem * GetPhysicsSystem()
    {
        return mPhysicsSystem;
    }

    /// Access to the temp allocator
    TempAllocator * GetTempAllocator()
    {
        return mTempAllocator;
    }

    /// Access the default object layer pair filter
    ObjectLayerPairFilter *GetObjectLayerPairFilter()
    {
        return mObjectLayerPairFilter;
    }

    /// Access the default object vs broadphase layer filter
    ObjectVsBroadPhaseLayerFilter *GetObjectVsBroadPhaseLayerFilter()
    {
        return mObjectVsBroadPhaseLayerFilter;
    }

//    /// Get the total reserved memory in bytes
//    /// See: https://github.com/emscripten-core/emscripten/blob/7459cab167138419168b5ac5eacf74702d5a3dae/test/core/test_mallinfo.c#L16-L18
//    static size_t sGetTotalMemory()
//    {
//        return (size_t)EM_ASM_PTR(return HEAP8.length);
//    }
//
//    /// Get the amount of free memory in bytes
//    /// See: https://github.com/emscripten-core/emscripten/blob/7459cab167138419168b5ac5eacf74702d5a3dae/test/core/test_mallinfo.c#L20-L25
//    static size_t sGetFreeMemory()
//    {
//        struct mallinfo i = mallinfo();
//        uintptr_t total_memory = sGetTotalMemory();
//        uintptr_t dynamic_top = (uintptr_t)sbrk(0);
//        return total_memory - dynamic_top + i.fordblks;
//    }

private:
    TempAllocatorImpl * mTempAllocator;
    JobSystemThreadPool mJobSystem { cMaxPhysicsJobs, cMaxPhysicsBarriers, min<int>(thread::hardware_concurrency() - 1, 16) }; // Limit to 16 threads since we limit the webworker thread pool size to this as well
    BroadPhaseLayerInterface *mBroadPhaseLayerInterface = nullptr;
    ObjectVsBroadPhaseLayerFilter *mObjectVsBroadPhaseLayerFilter = nullptr;
    ObjectLayerPairFilter * mObjectLayerPairFilter = nullptr;
    PhysicsSystem * mPhysicsSystem = nullptr;
};

/// Helper class to extract triangles from the shape
class ShapeGetTriangles
{
public:
    ShapeGetTriangles(const Shape *inShape, const AABox &inBox, Vec3Arg inPositionCOM, QuatArg inRotation, Vec3Arg inScale)
    {
        const size_t cBlockSize = 8096;

        // First collect all leaf shapes
        AllHitCollisionCollector<TransformedShapeCollector> collector;
        inShape->CollectTransformedShapes(inBox, inPositionCOM, inRotation, inScale, SubShapeIDCreator(), collector, { });

        size_t cur_pos = 0;

        // Iterate the leaf shapes
        for (const TransformedShape &ts : collector.mHits)
        {
            // Start iterating triangles
            Shape::GetTrianglesContext context;
            ts.GetTrianglesStart(context, inBox, RVec3::sZero());

            for (;;)
            {
                // Ensure we have space to get more triangles
                size_t tri_left = mMaterials.size() - cur_pos;
                if (tri_left < Shape::cGetTrianglesMinTrianglesRequested)
                {
                    mVertices.resize(mVertices.size() + 3 * cBlockSize);
                    mMaterials.resize(mMaterials.size() + cBlockSize);
                    tri_left = mMaterials.size() - cur_pos;
                }

                // Fetch next batch
                int count = ts.GetTrianglesNext(context, tri_left, mVertices.data() + 3 * cur_pos, mMaterials.data() + cur_pos);
                if (count == 0)
                {
                    // We're done
                    mVertices.resize(3 * cur_pos);
                    mMaterials.resize(cur_pos);
                    break;
                }

                cur_pos += count;
            }
        }

        // Free excess memory
        mVertices.shrink_to_fit();
        mMaterials.shrink_to_fit();
    }

    int GetNumTriangles() const
    {
        return (int)mMaterials.size();
    }

    int GetVerticesSize() const
    {
        return (int)mVertices.size() * sizeof(Float3);
    }

    const Float3 * GetVerticesData() const
    {
        return mVertices.data();
    }

    const PhysicsMaterial * GetMaterial(int inTriangle) const
    {
        return mMaterials[inTriangle];
    }

private:
    Array<Float3> mVertices;
    Array<const PhysicsMaterial *>	mMaterials;
};

/// A wrapper around ContactListener that is compatible with JavaScript
class ContactListenerEm: public ContactListener
{
public:
    // JavaScript compatible virtual functions
    virtual int OnContactValidate(const Body &inBody1, const Body &inBody2, const RVec3 *inBaseOffset, const CollideShapeResult &inCollisionResult) = 0;

    // Functions that call the JavaScript compatible virtual functions
    virtual ValidateResult	OnContactValidate(const Body &inBody1, const Body &inBody2, RVec3Arg inBaseOffset, const CollideShapeResult &inCollisionResult) override
    {
        return (ValidateResult)OnContactValidate(inBody1, inBody2, &inBaseOffset, inCollisionResult);
    }
};

/// A wrapper around SoftBodyContactListener that is compatible with JavaScript
class SoftBodyContactListenerEm: public SoftBodyContactListener
{
public:
    // JavaScript compatible virtual functions
    virtual int OnSoftBodyContactValidate(const Body &inSoftBody, const Body &inOtherBody, SoftBodyContactSettings *ioSettings) = 0;

    // Functions that call the JavaScript compatible virtual functions
    virtual SoftBodyValidateResult	OnSoftBodyContactValidate(const Body &inSoftBody, const Body &inOtherBody, SoftBodyContactSettings &ioSettings)
    {
        return (SoftBodyValidateResult)OnSoftBodyContactValidate(inSoftBody, inOtherBody, &ioSettings);
    }
};

/// A wrapper around CharacterContactListener that is compatible with JavaScript
class CharacterContactListenerEm: public CharacterContactListener
{
public:
    // JavaScript compatible virtual functions
    virtual void OnContactAdded(const CharacterVirtual *inCharacter, const BodyID &inBodyID2, const SubShapeID &inSubShapeID2, const RVec3 *inContactPosition, const Vec3 *inContactNormal, CharacterContactSettings &ioSettings) = 0;
    virtual void OnCharacterContactAdded(const CharacterVirtual *inCharacter, const CharacterVirtual *inOtherCharacter, const SubShapeID &inSubShapeID2, const RVec3 *inContactPosition, const Vec3 *inContactNormal, CharacterContactSettings &ioSettings) = 0;
    virtual void OnContactSolve(const CharacterVirtual *inCharacter, const BodyID &inBodyID2, const SubShapeID &inSubShapeID2, const RVec3 *inContactPosition, const Vec3 *inContactNormal, const Vec3 *inContactVelocity, const PhysicsMaterial *inContactMaterial, const Vec3 *inCharacterVelocity, Vec3 &ioNewCharacterVelocity) = 0;
    virtual void OnCharacterContactSolve(const CharacterVirtual *inCharacter, const CharacterVirtual *inOtherCharacter, const SubShapeID &inSubShapeID2, const RVec3 *inContactPosition, const Vec3 *inContactNormal, const Vec3 *inContactVelocity, const PhysicsMaterial *inContactMaterial, const Vec3 *inCharacterVelocity, Vec3 &ioNewCharacterVelocity) = 0;

    // Functions that call the JavaScript compatible virtual functions
    virtual void OnContactAdded(const CharacterVirtual *inCharacter, const BodyID &inBodyID2, const SubShapeID &inSubShapeID2, RVec3Arg inContactPosition, Vec3Arg inContactNormal, CharacterContactSettings &ioSettings) override
    {
        OnContactAdded(inCharacter, inBodyID2, inSubShapeID2, &inContactPosition, &inContactNormal, ioSettings);
    }

    virtual void OnCharacterContactAdded(const CharacterVirtual *inCharacter, const CharacterVirtual *inOtherCharacter, const SubShapeID &inSubShapeID2, RVec3Arg inContactPosition, Vec3Arg inContactNormal, CharacterContactSettings &ioSettings) override
    {
        OnCharacterContactAdded(inCharacter, inOtherCharacter, inSubShapeID2, &inContactPosition, &inContactNormal, ioSettings);
    }

    virtual void OnContactSolve(const CharacterVirtual *inCharacter, const BodyID &inBodyID2, const SubShapeID &inSubShapeID2, RVec3Arg inContactPosition, Vec3Arg inContactNormal, Vec3Arg inContactVelocity, const PhysicsMaterial *inContactMaterial, Vec3Arg inCharacterVelocity, Vec3 &ioNewCharacterVelocity) override
    {
        OnContactSolve(inCharacter, inBodyID2, inSubShapeID2, &inContactPosition, &inContactNormal, &inContactVelocity, inContactMaterial, &inCharacterVelocity, ioNewCharacterVelocity);
    }

    virtual void OnCharacterContactSolve(const CharacterVirtual *inCharacter, const CharacterVirtual *inOtherCharacter, const SubShapeID &inSubShapeID2, RVec3Arg inContactPosition, Vec3Arg inContactNormal, Vec3Arg inContactVelocity, const PhysicsMaterial *inContactMaterial, Vec3Arg inCharacterVelocity, Vec3 &ioNewCharacterVelocity) override
    {
        OnCharacterContactSolve(inCharacter, inOtherCharacter, inSubShapeID2, &inContactPosition, &inContactNormal, &inContactVelocity, inContactMaterial, &inCharacterVelocity, ioNewCharacterVelocity);
    }
};

/// A wrapper around the physics step listener that is compatible with JavaScript (JS doesn't like multiple inheritance)
class VehicleConstraintStepListener : public PhysicsStepListener
{
public:
    VehicleConstraintStepListener(VehicleConstraint *inVehicleConstraint)
    {
        mInstance = inVehicleConstraint;
    }

    virtual void OnStep(float inDeltaTime, PhysicsSystem &inPhysicsSystem) override
    {
        PhysicsStepListener* instance = mInstance;
        instance->OnStep(inDeltaTime, inPhysicsSystem);
    }

private:
    VehicleConstraint * mInstance;
};

/// Wrapper class around ObjectVsBroadPhaseLayerFilter to make it compatible with JavaScript (JS cannot pass parameter by value)
class ObjectVsBroadPhaseLayerFilterEm : public ObjectVsBroadPhaseLayerFilter
{
public:
    virtual bool ShouldCollide(ObjectLayer inLayer1, BroadPhaseLayer *inLayer2) const = 0;

    virtual bool ShouldCollide(ObjectLayer inLayer1, BroadPhaseLayer inLayer2) const
    {
        return ShouldCollide(inLayer1, &inLayer2);
    }
};

/// Wrapper class around BroadPhaseLayerInterface to make it compatible with JavaScript (JS cannot return parameter by value)
class BroadPhaseLayerInterfaceEm : public BroadPhaseLayerInterface
{
public:
    virtual unsigned short GetBPLayer(ObjectLayer inLayer) const = 0;

    virtual BroadPhaseLayer	GetBroadPhaseLayer(ObjectLayer inLayer) const override
    {
        return BroadPhaseLayer(GetBPLayer(inLayer));
    }

#if defined(JPH_EXTERNAL_PROFILE) || defined(JPH_PROFILE_ENABLED)
    /// Get the user readable name of a broadphase layer (debugging purposes)
    virtual const char * GetBroadPhaseLayerName(BroadPhaseLayer inLayer) const override
    {
        return "Undefined";
    }
#endif // JPH_EXTERNAL_PROFILE || JPH_PROFILE_ENABLED
};

/// A wrapper around the vehicle constraint callbacks that is compatible with JavaScript
class VehicleConstraintCallbacksEm
{
public:
    virtual ~VehicleConstraintCallbacksEm() = default;

    void SetVehicleConstraint(VehicleConstraint &inConstraint)
    {
        inConstraint.SetCombineFriction([this](uint inWheelIndex, float &ioLongitudinalFriction, float &ioLateralFriction, const Body &inBody2, const SubShapeID &inSubShapeID2) {
            ioLongitudinalFriction = GetCombinedFriction(inWheelIndex, ETireFrictionDirection_Longitudinal, ioLongitudinalFriction, inBody2, inSubShapeID2);
            ioLateralFriction = GetCombinedFriction(inWheelIndex, ETireFrictionDirection_Lateral, ioLateralFriction, inBody2, inSubShapeID2);
        });
        inConstraint.SetPreStepCallback([this](VehicleConstraint &inVehicle, float inDeltaTime, PhysicsSystem &inPhysicsSystem) {
            OnPreStepCallback(inVehicle, inDeltaTime, inPhysicsSystem);
        });
        inConstraint.SetPostCollideCallback([this](VehicleConstraint &inVehicle, float inDeltaTime, PhysicsSystem &inPhysicsSystem) {
            OnPostCollideCallback(inVehicle, inDeltaTime, inPhysicsSystem);
        });
        inConstraint.SetPostStepCallback([this](VehicleConstraint &inVehicle, float inDeltaTime, PhysicsSystem &inPhysicsSystem) {
            OnPostStepCallback(inVehicle, inDeltaTime, inPhysicsSystem);
        });
    }

    virtual float GetCombinedFriction(unsigned int inWheelIndex, ETireFrictionDirection inTireFrictionDirection, float inTireFriction, const Body &inBody2, const SubShapeID &inSubShapeID2) = 0;
    virtual void OnPreStepCallback(VehicleConstraint &inVehicle, float inDeltaTime, PhysicsSystem &inPhysicsSystem) = 0;
    virtual void OnPostCollideCallback(VehicleConstraint &inVehicle, float inDeltaTime, PhysicsSystem &inPhysicsSystem) = 0;
    virtual void OnPostStepCallback(VehicleConstraint &inVehicle, float inDeltaTime, PhysicsSystem &inPhysicsSystem) = 0;
};

/// The tire max impulse callback returns multiple parameters, so we need to store them in a class
class TireMaxImpulseCallbackResult
{
public:
    float mLongitudinalImpulse;
    float mLateralImpulse;
};

/// A wrapper around the wheeled vehicle controller callbacks that is compatible with JavaScript
class WheeledVehicleControllerCallbacksEm
{
public:
    virtual ~WheeledVehicleControllerCallbacksEm() = default;

    void SetWheeledVehicleController(WheeledVehicleController &inController)
    {
        inController.SetTireMaxImpulseCallback([this](uint inWheelIndex, float &outLongitudinalImpulse, float &outLateralImpulse, float inSuspensionImpulse, float inLongitudinalFriction, float inLateralFriction, float inLongitudinalSlip, float inLateralSlip, float inDeltaTime) {
            // Pre-fill the structure with default calculated values
            TireMaxImpulseCallbackResult result;
            result.mLongitudinalImpulse = inLongitudinalFriction * inSuspensionImpulse;
            result.mLateralImpulse = inLateralFriction * inSuspensionImpulse;

            OnTireMaxImpulseCallback(inWheelIndex, &result, inSuspensionImpulse, inLongitudinalFriction, inLateralFriction, inLongitudinalSlip, inLateralSlip, inDeltaTime);

            // Read the results
            outLongitudinalImpulse = result.mLongitudinalImpulse;
            outLateralImpulse = result.mLateralImpulse;
        });
    }

    virtual void OnTireMaxImpulseCallback(uint inWheelIndex, TireMaxImpulseCallbackResult *outResult, float inSuspensionImpulse, float inLongitudinalFriction, float inLateralFriction, float inLongitudinalSlip, float inLateralSlip, float inDeltaTime) = 0;
};

class PathConstraintPathEm: public PathConstraintPath
{
public:
    virtual float  GetClosestPoint(Vec3Arg inPosition, float inFractionHint) const
    {
        return GetClosestPoint(&inPosition, inFractionHint);
    }

    virtual void GetPointOnPath(float inFraction, Vec3 &outPathPosition, Vec3 &outPathTangent, Vec3 &outPathNormal, Vec3 &outPathBinormal) const
    {
        GetPointOnPath(inFraction, &outPathPosition, &outPathTangent, &outPathNormal, &outPathBinormal);
    }

    virtual float GetClosestPoint(const Vec3 *inPosition, float inFractionHint) const = 0;
    virtual void GetPointOnPath(float inFraction, Vec3 *outPathPosition, Vec3 *outPathTangent, Vec3 *outPathNormal, Vec3 *outPathBinormal) const = 0;
};

class HeightFieldShapeConstantValues
{
public:
    /// Value used to create gaps in the height field
    static constexpr float cNoCollisionValue = HeightFieldShapeConstants::cNoCollisionValue;
};

// DEBUG RENDERER

#include "Jolt/Renderer/DebugRendererSimple.h"

using BodyManagerDrawSettings = BodyManager::DrawSettings;
using DebugRendererVertex = DebugRenderer::Vertex;
using DebugRendererTriangle = DebugRenderer::Triangle;

using ECullMode = DebugRenderer::ECullMode;
constexpr ECullMode ECullMode_CullBackFace = ECullMode::CullBackFace;
constexpr ECullMode ECullMode_CullFrontFace = ECullMode::CullFrontFace;
constexpr ECullMode ECullMode_Off = ECullMode::Off;

using ECastShadow = DebugRenderer::ECastShadow;
constexpr ECastShadow ECastShadow_On = ECastShadow::On;
constexpr ECastShadow ECastShadow_Off = ECastShadow::Off;

using EDrawMode = DebugRenderer::EDrawMode;
constexpr EDrawMode EDrawMode_Solid = EDrawMode::Solid;
constexpr EDrawMode EDrawMode_Wireframe = EDrawMode::Wireframe;

using EShapeColor = BodyManager::EShapeColor;
constexpr EShapeColor EShapeColor_InstanceColor = EShapeColor::InstanceColor;
constexpr EShapeColor EShapeColor_ShapeTypeColor = EShapeColor::ShapeTypeColor;
constexpr EShapeColor EShapeColor_MotionTypeColor = EShapeColor::MotionTypeColor;
constexpr EShapeColor EShapeColor_SleepColor = EShapeColor::SleepColor;
constexpr EShapeColor EShapeColor_IslandColor = EShapeColor::IslandColor;
constexpr EShapeColor EShapeColor_MaterialColor = EShapeColor::MaterialColor;

constexpr ESoftBodyConstraintColor ESoftBodyConstraintColor_ConstraintType = ESoftBodyConstraintColor::ConstraintType;
constexpr ESoftBodyConstraintColor ESoftBodyConstraintColor_ConstraintGroup = ESoftBodyConstraintColor::ConstraintGroup;
constexpr ESoftBodyConstraintColor ESoftBodyConstraintColor_ConstraintOrder = ESoftBodyConstraintColor::ConstraintOrder;

class DebugRendererVertexTraits
{
    public:
        static constexpr uint mPositionOffset = offsetof(DebugRendererVertex, mPosition);
        static constexpr uint mNormalOffset = offsetof(DebugRendererVertex, mNormal);
        static constexpr uint mUVOffset = offsetof(DebugRendererVertex, mUV);
        static constexpr uint mSize = sizeof(DebugRendererVertex);
};

class DebugRendererTriangleTraits
{
    public:
        static constexpr uint mVOffset = offsetof(DebugRendererTriangle, mV);
        static constexpr uint mSize = sizeof(DebugRendererTriangle);
};

class ShapeFilterEm : public JPH::ShapeFilter
{
    public:

        virtual bool ShouldCollide_1(const Shape *inShape2, const SubShapeID &inSubShapeIDOfShape2) const = 0;
        virtual bool ShouldCollide_2(const Shape *inShape1, const SubShapeID &inSubShapeIDOfShape1, const Shape *inShape2, const SubShapeID &inSubShapeIDOfShape2) const = 0;

        virtual bool ShouldCollide(const Shape *inShape2, const SubShapeID &inSubShapeIDOfShape2) const
        {
            return ShouldCollide_1(inShape2, inSubShapeIDOfShape2);
        }

        virtual bool ShouldCollide(const Shape *inShape1, const SubShapeID &inSubShapeIDOfShape1, const Shape *inShape2, const SubShapeID &inSubShapeIDOfShape2) const
        {
            return ShouldCollide_2(inShape1, inSubShapeIDOfShape1, inShape2, inSubShapeIDOfShape2);
        }
};

class DebugRendererEm : public JPH::DebugRenderer
{
    public:
        void Initialize()
        {
            JPH::DebugRenderer::Initialize();
        }

        virtual void DrawLine(const RVec3 *inFrom, const RVec3 *inTo, const Color *inColor) = 0;

        virtual void DrawLine(RVec3Arg inFrom, RVec3Arg inTo, ColorArg inColor)
        {
            DrawLine(&inFrom, &inTo, &inColor);
        }

        virtual void DrawTriangle(const RVec3 *inV1, const RVec3 *inV2, const RVec3 *inV3, const Color *inColor, ECastShadow inCastShadow = ECastShadow::Off) = 0;

        virtual void DrawTriangle(RVec3Arg inV1, RVec3Arg inV2, RVec3Arg inV3, ColorArg inColor, ECastShadow inCastShadow = ECastShadow::Off)
        {
            DrawTriangle(&inV1, &inV2, &inV3, &inColor, inCastShadow);
        }

        virtual void DrawText3D(const RVec3 *inPosition, const void *inString, uint32 inStringLen, const Color *inColor, float inHeight) = 0;

        virtual void DrawText3D(RVec3Arg inPosition, const string_view &inString, ColorArg inColor, float inHeight)
        {
            DrawText3D(&inPosition, (const void*)inString.data(), inString.size(), &inColor, inHeight);
        }

        virtual uint32 CreateTriangleBatchID(const void *inTriangles, int inTriangleCount) = 0;

        virtual Batch CreateTriangleBatch(const Triangle *inTriangles, int inTriangleCount)
        {
            uint32 batch = CreateTriangleBatchID((const void*)inTriangles, inTriangleCount);
            return new BatchImpl(batch);
        }

        virtual uint32 CreateTriangleBatchIDWithIndex(const void *inVertices, int inVertexCount, const void *inIndices, int inIndexCount) = 0;

        virtual Batch CreateTriangleBatch(const Vertex *inVertices, int inVertexCount, const uint32 *inIndices, int inIndexCount)
        {
            uint32 batch = CreateTriangleBatchIDWithIndex((const void*)inVertices, inVertexCount, (const void*)inIndices, inIndexCount);
            return new BatchImpl(batch);
        }

        virtual void DrawGeometryWithID(const RMat44 *inModelMatrix, const AABox *inWorldSpaceBounds, float inLODScaleSq, Color *inModelColor, const uint32 inGeometryID, ECullMode inCullMode, ECastShadow inCastShadow, EDrawMode inDrawMode) = 0;

        virtual void DrawGeometry(RMat44Arg inModelMatrix, const AABox& inWorldSpaceBounds, float inLODScaleSq, ColorArg inModelColor, const GeometryRef& inGeometry, ECullMode inCullMode, ECastShadow inCastShadow, EDrawMode inDrawMode)
        {
            const LOD *lod = inGeometry->mLODs.data();
            const BatchImpl *batch = static_cast<const BatchImpl*>(lod->mTriangleBatch.GetPtr());

            DrawGeometryWithID(&inModelMatrix, &inWorldSpaceBounds, inLODScaleSq, &inModelColor, batch->mID, inCullMode, inCastShadow, inDrawMode);
        }

        void DrawBodies(PhysicsSystem *inSystem, BodyManager::DrawSettings *inDrawSettings)
        {
            inSystem->DrawBodies(*inDrawSettings, this);
        }
        void DrawBodies(PhysicsSystem *inSystem)
        {
            inSystem->DrawBodies(BodyManager::DrawSettings(), this);
        }

        void DrawConstraints(PhysicsSystem *inSystem)
        {
            inSystem->DrawConstraints(this);
        }

        void DrawConstraintLimits(PhysicsSystem *inSystem)
        {
            inSystem->DrawConstraintLimits(this);
        }

        void DrawConstraintReferenceFrame(PhysicsSystem *inSystem)
        {
            inSystem->DrawConstraintReferenceFrame(this);
        }

        void DrawShape(Shape *inShape, const RMat44 *inModelMatrix, const RVec3 *inScale, const Color *inColor, bool inDrawWireFrame)
        {
            inShape->Draw(this, *inModelMatrix, *inScale, *inColor, false, inDrawWireFrame);
        }

        void DrawBody(Body *inBody, const Color *inColor, bool inDrawWireFrame)
        {
            RMat44 com = inBody->GetCenterOfMassTransform();
            inBody->GetShape()->Draw(this, com, Vec3::sReplicate(1.0f), *inColor, false, inDrawWireFrame);
        }

        void DrawConstraint(Constraint *inConstraint)
        {
            inConstraint->DrawConstraint(this);
        }

    private:
        /// Implementation specific batch object
        class BatchImpl : public RefTargetVirtual
        {
            public:
                JPH_OVERRIDE_NEW_DELETE

                BatchImpl(uint32 inID) : mID(inID) {  }

                virtual void AddRef() override { ++mRefCount; }
                virtual void Release() override { if (--mRefCount == 0) delete this; }

                atomic<uint32> mRefCount = 0;
                uint32 mID;
        };
};