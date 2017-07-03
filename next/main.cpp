#undef SLOT

#include <ecl/ecl.h>
#include <QApplication>
#include <QTextCodec>
#include <QSettings>
#include <QTranslator>
#include "eql5/eql.h"

extern "C" void ini_app(cl_object);

int catch_all_qexec() {
    int ret = 0;
    CL_CATCH_ALL_BEGIN(ecl_process_env()) {
        ret = QApplication::exec(); }
    CL_CATCH_ALL_END;
    return ret; }

int main(int argc, char** argv) {

    EQL::ini(argv); // best initialized here

    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts); // for Qt WebEngine
    QApplication qapp(argc, argv);

    QTextCodec* utf8 = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(utf8);

    EQL eql;

#ifdef Q_OS_WIN
    // print output would crash program
    eql.ignoreIOStreams();
#endif

    eql.exec(ini_app,    // see make.lisp
             "(start)",  // initial form to be evaluated (optional)
             "next");    // package name                 (optional)

    return catch_all_qexec(); } // closing the main/last window will quit the program
