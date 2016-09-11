// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	C++ class header boilerplate exported from UnrealHeaderTool.
	This is automatically generated by the tools.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectBase.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef SUBEARTH_SubEarthHUD_generated_h
#error "SubEarthHUD.generated.h already included, missing '#pragma once' in SubEarthHUD.h"
#endif
#define SUBEARTH_SubEarthHUD_generated_h

#define SubEarth_Source_SubEarth_SubEarthHUD_h_9_RPC_WRAPPERS
#define SubEarth_Source_SubEarth_SubEarthHUD_h_9_RPC_WRAPPERS_NO_PURE_DECLS
#define SubEarth_Source_SubEarth_SubEarthHUD_h_9_INCLASS_NO_PURE_DECLS \
	private: \
	static void StaticRegisterNativesASubEarthHUD(); \
	friend SUBEARTH_API class UClass* Z_Construct_UClass_ASubEarthHUD(); \
	public: \
	DECLARE_CLASS(ASubEarthHUD, AHUD, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), 0, TEXT("/Script/SubEarth"), NO_API) \
	DECLARE_SERIALIZER(ASubEarthHUD) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define SubEarth_Source_SubEarth_SubEarthHUD_h_9_INCLASS \
	private: \
	static void StaticRegisterNativesASubEarthHUD(); \
	friend SUBEARTH_API class UClass* Z_Construct_UClass_ASubEarthHUD(); \
	public: \
	DECLARE_CLASS(ASubEarthHUD, AHUD, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), 0, TEXT("/Script/SubEarth"), NO_API) \
	DECLARE_SERIALIZER(ASubEarthHUD) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define SubEarth_Source_SubEarth_SubEarthHUD_h_9_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ASubEarthHUD(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ASubEarthHUD) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASubEarthHUD); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASubEarthHUD); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ASubEarthHUD(ASubEarthHUD&&); \
	NO_API ASubEarthHUD(const ASubEarthHUD&); \
public:


#define SubEarth_Source_SubEarth_SubEarthHUD_h_9_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ASubEarthHUD(ASubEarthHUD&&); \
	NO_API ASubEarthHUD(const ASubEarthHUD&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASubEarthHUD); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASubEarthHUD); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ASubEarthHUD)


#define SubEarth_Source_SubEarth_SubEarthHUD_h_6_PROLOG
#define SubEarth_Source_SubEarth_SubEarthHUD_h_9_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SubEarth_Source_SubEarth_SubEarthHUD_h_9_RPC_WRAPPERS \
	SubEarth_Source_SubEarth_SubEarthHUD_h_9_INCLASS \
	SubEarth_Source_SubEarth_SubEarthHUD_h_9_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define SubEarth_Source_SubEarth_SubEarthHUD_h_9_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SubEarth_Source_SubEarth_SubEarthHUD_h_9_RPC_WRAPPERS_NO_PURE_DECLS \
	SubEarth_Source_SubEarth_SubEarthHUD_h_9_INCLASS_NO_PURE_DECLS \
	SubEarth_Source_SubEarth_SubEarthHUD_h_9_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID SubEarth_Source_SubEarth_SubEarthHUD_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
