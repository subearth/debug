// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	C++ class header boilerplate exported from UnrealHeaderTool.
	This is automatically generated by the tools.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectBase.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UPrimitiveComponent;
class AActor;
struct FHitResult;
#ifdef SUBEARTH_SubEarthCharacter_generated_h
#error "SubEarthCharacter.generated.h already included, missing '#pragma once' in SubEarthCharacter.h"
#endif
#define SUBEARTH_SubEarthCharacter_generated_h

#define SubEarth_Source_SubEarth_CharacterControl_SubEarthCharacter_h_20_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execHeartTriggerExit) \
	{ \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_overlappedComponent); \
		P_GET_OBJECT(AActor,Z_Param_otherActor); \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_otherComponent); \
		P_GET_PROPERTY(UIntProperty,Z_Param_otherBodyIndex); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->HeartTriggerExit(Z_Param_overlappedComponent,Z_Param_otherActor,Z_Param_otherComponent,Z_Param_otherBodyIndex); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execHeartTriggerEnter) \
	{ \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_overlappedComponent); \
		P_GET_OBJECT(AActor,Z_Param_otherActor); \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_otherComponent); \
		P_GET_PROPERTY(UIntProperty,Z_Param_otherBodyIndex); \
		P_GET_UBOOL(Z_Param_bFromSweep); \
		P_GET_STRUCT_REF(FHitResult,Z_Param_Out_SweepResult); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->HeartTriggerEnter(Z_Param_overlappedComponent,Z_Param_otherActor,Z_Param_otherComponent,Z_Param_otherBodyIndex,Z_Param_bFromSweep,Z_Param_Out_SweepResult); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execUpdateCurrentOxygen) \
	{ \
		P_GET_PROPERTY(UFloatProperty,Z_Param_Oxygen); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(float*)Z_Param__Result=this->UpdateCurrentOxygen(Z_Param_Oxygen); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetCurrentOxygen) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(float*)Z_Param__Result=this->GetCurrentOxygen(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetInitialOxygen) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(float*)Z_Param__Result=this->GetInitialOxygen(); \
		P_NATIVE_END; \
	}


#define SubEarth_Source_SubEarth_CharacterControl_SubEarthCharacter_h_20_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execHeartTriggerExit) \
	{ \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_overlappedComponent); \
		P_GET_OBJECT(AActor,Z_Param_otherActor); \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_otherComponent); \
		P_GET_PROPERTY(UIntProperty,Z_Param_otherBodyIndex); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->HeartTriggerExit(Z_Param_overlappedComponent,Z_Param_otherActor,Z_Param_otherComponent,Z_Param_otherBodyIndex); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execHeartTriggerEnter) \
	{ \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_overlappedComponent); \
		P_GET_OBJECT(AActor,Z_Param_otherActor); \
		P_GET_OBJECT(UPrimitiveComponent,Z_Param_otherComponent); \
		P_GET_PROPERTY(UIntProperty,Z_Param_otherBodyIndex); \
		P_GET_UBOOL(Z_Param_bFromSweep); \
		P_GET_STRUCT_REF(FHitResult,Z_Param_Out_SweepResult); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->HeartTriggerEnter(Z_Param_overlappedComponent,Z_Param_otherActor,Z_Param_otherComponent,Z_Param_otherBodyIndex,Z_Param_bFromSweep,Z_Param_Out_SweepResult); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execUpdateCurrentOxygen) \
	{ \
		P_GET_PROPERTY(UFloatProperty,Z_Param_Oxygen); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(float*)Z_Param__Result=this->UpdateCurrentOxygen(Z_Param_Oxygen); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetCurrentOxygen) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(float*)Z_Param__Result=this->GetCurrentOxygen(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetInitialOxygen) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(float*)Z_Param__Result=this->GetInitialOxygen(); \
		P_NATIVE_END; \
	}


#define SubEarth_Source_SubEarth_CharacterControl_SubEarthCharacter_h_20_INCLASS_NO_PURE_DECLS \
	private: \
	static void StaticRegisterNativesASubEarthCharacter(); \
	friend SUBEARTH_API class UClass* Z_Construct_UClass_ASubEarthCharacter(); \
	public: \
	DECLARE_CLASS(ASubEarthCharacter, ACharacter, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/SubEarth"), NO_API) \
	DECLARE_SERIALIZER(ASubEarthCharacter) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define SubEarth_Source_SubEarth_CharacterControl_SubEarthCharacter_h_20_INCLASS \
	private: \
	static void StaticRegisterNativesASubEarthCharacter(); \
	friend SUBEARTH_API class UClass* Z_Construct_UClass_ASubEarthCharacter(); \
	public: \
	DECLARE_CLASS(ASubEarthCharacter, ACharacter, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/SubEarth"), NO_API) \
	DECLARE_SERIALIZER(ASubEarthCharacter) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define SubEarth_Source_SubEarth_CharacterControl_SubEarthCharacter_h_20_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ASubEarthCharacter(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ASubEarthCharacter) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASubEarthCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASubEarthCharacter); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ASubEarthCharacter(ASubEarthCharacter&&); \
	NO_API ASubEarthCharacter(const ASubEarthCharacter&); \
public:


#define SubEarth_Source_SubEarth_CharacterControl_SubEarthCharacter_h_20_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ASubEarthCharacter(ASubEarthCharacter&&); \
	NO_API ASubEarthCharacter(const ASubEarthCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASubEarthCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASubEarthCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ASubEarthCharacter)


#define SubEarth_Source_SubEarth_CharacterControl_SubEarthCharacter_h_17_PROLOG
#define SubEarth_Source_SubEarth_CharacterControl_SubEarthCharacter_h_20_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SubEarth_Source_SubEarth_CharacterControl_SubEarthCharacter_h_20_RPC_WRAPPERS \
	SubEarth_Source_SubEarth_CharacterControl_SubEarthCharacter_h_20_INCLASS \
	SubEarth_Source_SubEarth_CharacterControl_SubEarthCharacter_h_20_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define SubEarth_Source_SubEarth_CharacterControl_SubEarthCharacter_h_20_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SubEarth_Source_SubEarth_CharacterControl_SubEarthCharacter_h_20_RPC_WRAPPERS_NO_PURE_DECLS \
	SubEarth_Source_SubEarth_CharacterControl_SubEarthCharacter_h_20_INCLASS_NO_PURE_DECLS \
	SubEarth_Source_SubEarth_CharacterControl_SubEarthCharacter_h_20_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID SubEarth_Source_SubEarth_CharacterControl_SubEarthCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
