

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0499 */
/* at Wed Sep 17 03:51:44 2008
 */
/* Compiler settings for .\VistaFolderBackground.idl:
    Oicf, W1, Zp8, env=Win64 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __VistaFolderBackground_h__
#define __VistaFolderBackground_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IAveVistaBackgroundFolder_FWD_DEFINED__
#define __IAveVistaBackgroundFolder_FWD_DEFINED__
typedef interface IAveVistaBackgroundFolder IAveVistaBackgroundFolder;
#endif 	/* __IAveVistaBackgroundFolder_FWD_DEFINED__ */


#ifndef __IShellExtConfigEntry_FWD_DEFINED__
#define __IShellExtConfigEntry_FWD_DEFINED__
typedef interface IShellExtConfigEntry IShellExtConfigEntry;
#endif 	/* __IShellExtConfigEntry_FWD_DEFINED__ */


#ifndef __AveVistaBackgroundFolder_FWD_DEFINED__
#define __AveVistaBackgroundFolder_FWD_DEFINED__

#ifdef __cplusplus
typedef class AveVistaBackgroundFolder AveVistaBackgroundFolder;
#else
typedef struct AveVistaBackgroundFolder AveVistaBackgroundFolder;
#endif /* __cplusplus */

#endif 	/* __AveVistaBackgroundFolder_FWD_DEFINED__ */


#ifndef __ShellExtConfigEntry_FWD_DEFINED__
#define __ShellExtConfigEntry_FWD_DEFINED__

#ifdef __cplusplus
typedef class ShellExtConfigEntry ShellExtConfigEntry;
#else
typedef struct ShellExtConfigEntry ShellExtConfigEntry;
#endif /* __cplusplus */

#endif 	/* __ShellExtConfigEntry_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IAveVistaBackgroundFolder_INTERFACE_DEFINED__
#define __IAveVistaBackgroundFolder_INTERFACE_DEFINED__

/* interface IAveVistaBackgroundFolder */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAveVistaBackgroundFolder;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("243F31ED-7429-4CBC-A0F7-26223D9762DE")
    IAveVistaBackgroundFolder : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE InitMe( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAveVistaBackgroundFolderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAveVistaBackgroundFolder * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAveVistaBackgroundFolder * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAveVistaBackgroundFolder * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *InitMe )( 
            IAveVistaBackgroundFolder * This);
        
        END_INTERFACE
    } IAveVistaBackgroundFolderVtbl;

    interface IAveVistaBackgroundFolder
    {
        CONST_VTBL struct IAveVistaBackgroundFolderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAveVistaBackgroundFolder_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAveVistaBackgroundFolder_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAveVistaBackgroundFolder_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAveVistaBackgroundFolder_InitMe(This)	\
    ( (This)->lpVtbl -> InitMe(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAveVistaBackgroundFolder_INTERFACE_DEFINED__ */


#ifndef __IShellExtConfigEntry_INTERFACE_DEFINED__
#define __IShellExtConfigEntry_INTERFACE_DEFINED__

/* interface IShellExtConfigEntry */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IShellExtConfigEntry;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E497DEED-DEA4-4388-816C-7F1ADB334B94")
    IShellExtConfigEntry : public IUnknown
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IShellExtConfigEntryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IShellExtConfigEntry * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IShellExtConfigEntry * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IShellExtConfigEntry * This);
        
        END_INTERFACE
    } IShellExtConfigEntryVtbl;

    interface IShellExtConfigEntry
    {
        CONST_VTBL struct IShellExtConfigEntryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IShellExtConfigEntry_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IShellExtConfigEntry_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IShellExtConfigEntry_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IShellExtConfigEntry_INTERFACE_DEFINED__ */



#ifndef __VistaFolderBackgroundLib_LIBRARY_DEFINED__
#define __VistaFolderBackgroundLib_LIBRARY_DEFINED__

/* library VistaFolderBackgroundLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_VistaFolderBackgroundLib;

EXTERN_C const CLSID CLSID_AveVistaBackgroundFolder;

#ifdef __cplusplus

class DECLSPEC_UUID("73526E5A-FD53-4BE7-B5E2-D3C89D7413DC")
AveVistaBackgroundFolder;
#endif

EXTERN_C const CLSID CLSID_ShellExtConfigEntry;

#ifdef __cplusplus

class DECLSPEC_UUID("B1E4711E-9386-4927-9291-6FFC49631520")
ShellExtConfigEntry;
#endif
#endif /* __VistaFolderBackgroundLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


