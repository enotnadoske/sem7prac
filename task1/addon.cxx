#include "transp_part.hxx"
#include <com/sun/star/beans/PropertyValue.hpp>
#include <com/sun/star/frame/XFrame.hpp>
#include <com/sun/star/frame/XController.hpp>
#include <com/sun/star/awt/Toolkit.hpp>
#include <com/sun/star/awt/XWindowPeer.hpp>
#include <com/sun/star/awt/WindowAttribute.hpp>
#include <com/sun/star/uno/XComponentContext.hpp>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#include <rtl/ustring.hxx>
#include "addon.hxx"
#include <cppuhelper/supportsservice.hxx>
#include <iostream>

using rtl::OUString;
using namespace com::sun::star::uno;
using namespace com::sun::star::frame;
using namespace com::sun::star::awt;
using namespace com::sun::star::text;
using com::sun::star::beans::PropertyValue;
using com::sun::star::util::URL;

#define SERVICE_NAME "com.sun.star.frame.ProtocolHandler"


void SAL_CALL Addon::initialize(const Sequence<Any>& aArguments) throw (Exception, RuntimeException) {
    srand(time(0));
    Reference <XFrame> xFrame;
    if (aArguments.getLength()) {
        aArguments[0] >>= xFrame;
        mxFrame = xFrame;
    }
    mxToolkit = Reference<XToolkit>(Toolkit::create(mxContext), UNO_QUERY_THROW);
}


Reference<XDispatch> SAL_CALL Addon::queryDispatch(
    const URL& aURL,
    const ::rtl::OUString& sTargetFrameName,
    sal_Int32 nSearchFlags) throw(RuntimeException) {
    Reference <XDispatch> xRet;
    if (aURL.Protocol.equalsAscii("org.openoffice.Office.table.transposition:")) {
        if (aURL.Path.equalsAscii("Transpose")) xRet = this;
        else if (aURL.Path.equalsAscii("NewDocument")) xRet = this;
        else if (aURL.Path.equalsAscii( "Help" )) xRet = this;
    }
    return xRet;
}


void SAL_CALL Addon::dispatch(const URL& aURL, const Sequence <PropertyValue>& lArgs) throw (RuntimeException) {
    if (aURL.Protocol.equalsAscii("org.openoffice.Office.table.transposition:")) {
        if (aURL.Path.equalsAscii("Transpose")) {
            Reference<XTextDocument> text_document(mxFrame->getController()->getModel(), UNO_QUERY);
            transposeTable(text_document);
        } else if (aURL.Path.equalsAscii("NewDocument")) {
            newDoc(mxContext);
        }
    }
}


Sequence <Reference<XDispatch>> SAL_CALL Addon::queryDispatches(const Sequence <DispatchDescriptor>& seqDescripts) throw(RuntimeException) {
    sal_Int32 nCount = seqDescripts.getLength();
    Sequence <Reference<XDispatch>> lDispatcher(nCount);

    for(sal_Int32 i = 0; i < nCount; i++)
        lDispatcher[i] = queryDispatch(seqDescripts[i].FeatureURL, seqDescripts[i].FrameName, seqDescripts[i].SearchFlags);

    return lDispatcher;
}


void SAL_CALL Addon::addStatusListener(const Reference< XStatusListener >& xControl, const URL& aURL) throw (RuntimeException) {}
void SAL_CALL Addon::removeStatusListener(const Reference< XStatusListener >& xControl, const URL& aURL) throw (RuntimeException) {}


OUString Addon_getImplementationName() throw (RuntimeException) {return OUString(IMPLEMENTATION_NAME);}


Sequence<::rtl::OUString> SAL_CALL Addon_getSupportedServiceNames() throw (RuntimeException) {
    Sequence <::rtl::OUString> aRet(1);
    ::rtl::OUString* pArray = aRet.getArray();

    pArray[0] = OUString(SERVICE_NAME);
    return aRet;
}


Reference<XInterface> SAL_CALL Addon_createInstance(const Reference<XComponentContext> & rContext) throw(Exception) {
    return (cppu::OWeakObject*) new Addon(rContext);
}


OUString SAL_CALL Addon::getImplementationName() throw (RuntimeException) {
    return Addon_getImplementationName();
}


sal_Bool SAL_CALL Addon::supportsService(const OUString& rServiceName) throw (RuntimeException) {
    return cppu::supportsService(this, rServiceName);
}


Sequence<OUString> SAL_CALL Addon::getSupportedServiceNames() throw (RuntimeException) {
    return Addon_getSupportedServiceNames();
}
