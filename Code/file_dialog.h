// Part of GardenGrow.

#ifndef FILE_DIALOG_H
#define FILE_DIALOG_H

// A platform independant interface to open a file select dialog

#include <string>

enum ggDialogType { DIALOG_OPEN, DIALOG_SAVE };

std::string pop_file_dialog( ggDialogType argType, std::string argStartPath );

#endif