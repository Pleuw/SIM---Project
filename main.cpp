#include <qapplication.h>
#include <QString>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "viewer.h"

using namespace std;

char *getFilename(int argc,char **argv) {
  if(argc<2) {
    cout << "Usage: " << argv[0] << " offFile" << endl;
    exit(0);
  }

  return argv[1];
}

int main(int argc,char** argv) {
  QApplication application(argc,argv);

  QGLFormat fmt;
  fmt.setVersion(3,3);
  fmt.setProfile(QGLFormat::CoreProfile);
  fmt.setSampleBuffers(true);
  
  Viewer viewer(getFilename(argc,argv),fmt);

  viewer.setWindowTitle("Exercice 04 - Shading");
  viewer.show();
  
  return application.exec();
}
