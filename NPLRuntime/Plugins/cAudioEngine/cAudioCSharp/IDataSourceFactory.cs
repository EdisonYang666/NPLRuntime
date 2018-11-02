/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.7
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

namespace cAudio {

using System;
using System.Runtime.InteropServices;

public class IDataSourceFactory : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal IDataSourceFactory(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(IDataSourceFactory obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~IDataSourceFactory() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          cAudioCSharpWrapperPINVOKE.delete_IDataSourceFactory(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

  public IDataSourceFactory() : this(cAudioCSharpWrapperPINVOKE.new_IDataSourceFactory(), true) {
    SwigDirectorConnect();
  }

  public virtual IDataSource CreateDataSource(string filename, bool streamingRequested) {
    IntPtr cPtr = cAudioCSharpWrapperPINVOKE.IDataSourceFactory_CreateDataSource(swigCPtr, filename, streamingRequested);
    IDataSource ret = (cPtr == IntPtr.Zero) ? null : new IDataSource(cPtr, false);
    return ret;
  }

  private void SwigDirectorConnect() {
    if (SwigDerivedClassHasMethod("CreateDataSource", swigMethodTypes0))
      swigDelegate0 = new SwigDelegateIDataSourceFactory_0(SwigDirectorCreateDataSource);
    cAudioCSharpWrapperPINVOKE.IDataSourceFactory_director_connect(swigCPtr, swigDelegate0);
  }

  private bool SwigDerivedClassHasMethod(string methodName, Type[] methodTypes) {
    System.Reflection.MethodInfo methodInfo = this.GetType().GetMethod(methodName, System.Reflection.BindingFlags.Public | System.Reflection.BindingFlags.NonPublic | System.Reflection.BindingFlags.Instance, null, methodTypes, null);
    bool hasDerivedMethod = methodInfo.DeclaringType.IsSubclassOf(typeof(IDataSourceFactory));
    return hasDerivedMethod;
  }

  private IntPtr SwigDirectorCreateDataSource(string filename, bool streamingRequested) {
    return IDataSource.getCPtr(CreateDataSource(filename, streamingRequested)).Handle;
  }

  public delegate IntPtr SwigDelegateIDataSourceFactory_0(string filename, bool streamingRequested);

  private SwigDelegateIDataSourceFactory_0 swigDelegate0;

  private static Type[] swigMethodTypes0 = new Type[] { typeof(string), typeof(bool) };
}

}
