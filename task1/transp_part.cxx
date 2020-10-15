#include "transp_part.hxx"
#include <iostream>
#include <com/sun/star/text/XTextTablesSupplier.hpp>
#include <com/sun/star/table/XTableRows.hpp>
#include <com/sun/star/table/XCellRange.hpp>
#include <com/sun/star/table/XTable.hpp>
#include <com/sun/star/frame/Desktop.hpp>
#include <algorithm>
#include <typeinfo>

using namespace com::sun::star::uno;
using namespace com::sun::star::lang;
using namespace com::sun::star::beans;
using namespace com::sun::star::frame;
using namespace com::sun::star::text;
using namespace com::sun::star::table;
using namespace com::sun::star::container;
using ::rtl::OUString;
using ::rtl::OUStringToOString;
using ::rtl::OString;



std::string makeCellName(uint64_t col,uint64_t row){
    std::string cell;
    cell+=(char)('A' + col);
    cell+=std::to_string(row + 1);
    return cell;
}

void fillTable(Reference <XTextTable> tbl, uint64_t col_num, uint64_t row_num){
    for(uint64_t col_cur = 0; col_cur < col_num; col_cur++){
        for(uint64_t row_cur = 0; row_cur < row_num; row_cur++){
            auto cur_cell_name = makeCellName(col_cur,row_cur).c_str();
            auto cur_cell = tbl->getCellByName(OUString::createFromAscii(cur_cell_name));
            auto cur_cell_val = (std::string("col - ") + std::to_string(col_cur + 1) + std::string(" row - ") + std::to_string(row_cur + 1));
            Reference<XText> cur_cell_txt(cur_cell, UNO_QUERY);
            cur_cell_txt->setString(OUString::createFromAscii(cur_cell_val.c_str()));
        }
    }
}


void newDoc(Reference<XComponentContext> xContext){
    Reference<XMultiComponentFactory> xServiceManager = xContext->getServiceManager();
    Reference<XInterface> xDesktop = xServiceManager->createInstanceWithContext(OUString("com.sun.star.frame.Desktop"), xContext);
    Reference<XDesktop2> xDesktop2(xDesktop, UNO_QUERY);
    Reference<XComponent> xComponent = xDesktop2->loadComponentFromURL(OUString("private:factory/swriter"), // URL to the ods file
                                            OUString( "_blank" ), 0,
                                            Sequence < ::com::sun::star::beans::PropertyValue >());
    Reference <XTextDocument> text_doc(xComponent, UNO_QUERY);
    Reference <XText> text = text_doc->getText();
    Reference <XMultiServiceFactory> doc(text_doc, UNO_QUERY);
    uint64_t tables_number = std::rand() % 7 + 2;
    for (uint64_t i = 0; i < tables_number; i++) {
        auto text_cursor = text->createTextCursor();
        auto table_name = "\nTable : " + std::to_string(i + 1);
        text_cursor->gotoEnd(false);
        text_cursor->setString(OUString::createFromAscii(table_name.c_str()));
        uint64_t row_num = std::rand() % 7 + 3;
        uint64_t col_num = std::rand() % 3 + 3;
        Reference <XTextTable> table(doc->createInstance(OUString::createFromAscii("com.sun.star.text.TextTable")), UNO_QUERY);
        table->initialize(row_num, col_num);
        auto text_range = text->getEnd();
        Reference <XTextContent> text_cont(table, UNO_QUERY);
        text->insertTextContent(text_range, text_cont, (unsigned char) 0);
        fillTable(table, col_num, row_num);
    }
}

uint64_t sqTableMaxSize(Reference<XTextTable> &tbl){
    auto curs = tbl->createCursorByCellName(OUString::createFromAscii("A1"));
    uint64_t col_count = 1;
    uint64_t row_count = 1;
    while (curs->goDown(1, false)) col_count += 1;
    while (curs->goRight(1, false)) row_count += 1;
    return std::min(col_count, row_count);
}



void transposeTable(Reference<XTextDocument> text_document) {
    Reference<XTextTablesSupplier> table_helper(text_document, UNO_QUERY);
    auto text_tables = table_helper->getTextTables();
    auto tables_names = text_tables->getElementNames();
    for (uint64_t i = 0; i < tables_names.getLength(); ++i) {
        Reference<XTextTable> table(text_tables->getByName(tables_names[i]), UNO_QUERY);
        auto max_sq = sqTableMaxSize(table);
        for (uint64_t col = 0; col < max_sq; ++col) {
            for (uint64_t row = col; row < max_sq; ++row) {
                Reference<XCell> cell_1 = table->getCellByName(OUString::createFromAscii(makeCellName(col, row).c_str()));
                Reference<XCell> cell_2 = table->getCellByName(OUString::createFromAscii(makeCellName(row, col).c_str()));
                Reference<XText> cell_1_text(cell_1, UNO_QUERY);
                Reference<XText> cell_2_text(cell_2, UNO_QUERY);
                auto tmp = cell_1_text->getString();
                cell_1_text->setString(cell_2_text->getString());
                cell_2_text->setString(tmp);
            }
        }
    }
}
