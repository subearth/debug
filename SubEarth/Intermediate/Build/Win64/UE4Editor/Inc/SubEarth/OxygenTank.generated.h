// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	C++ class header boilerplate exported from UnrealHeaderTool.
	This is automatically generated by the tools.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectBase.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef SUBEARTH_OxygenTank_generated_h
#error "OxygenTank.generated.h already included, missing '#pragma once' in OxygenTank.h"
#endif
#define SUBEARTH_OxygenTank_generated_h

#define SubEarth_Source_SubEarth_Objects_OxygenTank_h_14_RPC_WRAPPERS
#define SubEarth_Source_SubEarth_Objects_OxygenTank_h_14_RPC_WRAPPERS_NO_PURE_DECLS
#define SubEarth_Source_SubEarth_Objects_OxygenTank_h_14_INCLASS_NO_PURE_DECLS \
	private: \
	static void StaticRegisterNativesAOxygenTank(); \
	friend SUBEARTH_API class UClass* Z_Construct_UClass_AOxygenTank(); \
	public: \
	DECLARE_CLASS(AOxygenTank, APickup, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/SubEarth"), NO_API) \
	DECLARE_SERIALIZER(AOxygenTank) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define SubEarth_Source_SubEarth_Objects_OxygenTank_h_14_INCLASS \
	private: \
	static void StaticRegisterNativesAOxygenTank(); \
	friend SUBEARTH_API class UClass* Z_Construct_UClass_AOxygenTank(); \
	public: \
	DECLARE_CLASS(AOxygenTank, APickup, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/SubEarth"), NO_API) \
	DECLARE_SERIALIZER(AOxygenTank) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define SubEarth_Source_SubEarth_Objects_OxygenTank_h_14_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AOxygenTank(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AOxygenTank) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AOxygenTank); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AOxygenTank); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AOxygenTank(AOxygenTank&&); \
	NO_API AOxygenTank(const AOxygenTank&); \
public:


#define SubEarth_Source_SubEarth_Objects_OxygenTank_h_14_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AOxygenTank(AOxygenTank&&); \
	NO_API AOxygenTank(const AOxygenTank&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AOxygenTank); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AOxygenTank); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AOxygenTank)


#define SubEarth_Source_SubEarth_Objects_OxygenTank_h_11_PROLOG
#define SubEarth_Source_SubEarth_Objects_OxygenTank_h_14_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SubEarth_Source_SubEarth_Objects_OxygenTank_h_14_RPC_WRAPPERS \
	SubEarth_Source_SubEarth_Objects_OxygenTank_h_14_INCLASS \
	SubEarth_Source_SubEarth_Objects_OxygenTank_h_14_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define SubEarth_Source_SubEarth_Objects_OxygenTank_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SubEarth_Source_SubEarth_Objects_OxygenTank_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	SubEarth_Source_SubEarth_Objects_OxygenTank_h_14_INCLASS_NO_PURE_DECLS \
	SubEarth_Source_SubEarth_Objects_OxygenTank_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID SubEarth_Source_SubEarth_Objects_OxygenTank_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
