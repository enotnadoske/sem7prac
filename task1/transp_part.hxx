#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#include <com/sun/star/text/XTextDocument.hpp>
#include <com/sun/star/text/XText.hpp>
#include <com/sun/star/text/XTextTable.hpp>
#include <com/sun/star/text/XTextContent.hpp>
#include <com/sun/star/table/XCell.hpp>
#include <com/sun/star/lang/XMultiComponentFactory.hpp>
#include <com/sun/star/frame/XComponentLoader.hpp>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace com::sun::star::uno;
using namespace com::sun::star::lang;
using namespace com::sun::star::beans;
using namespace com::sun::star::frame;
using namespace com::sun::star::text;
using namespace com::sun::star::table;

using ::rtl::OUString;
using ::rtl::OUStringToOString;
using ::rtl::OString;

void transposeTable(Reference <XTextDocument> text_document);

void fillTable(Reference <XTextTable> table, int num_of_col, int num_of_row);

void newDoc(Reference<XComponentContext> xContext);

void newTable(Reference <XMultiServiceFactory> document, Reference <XText> text);

uint64_t sqTableMaxSize(Reference<XTextTable> &tbl);

std::string makeCellName(uint64_t col,uint64_t row);
