# QExtenedTableWidget

This is an extended version of the QTableWidget with a button to show/hide specific columns.

Improvements and commtens are very welcome :)

### Functions / API

These are the main functions:

This subclassed QTableWidget shows a button in the top right corner which shows a QMenu if clicked. This QMenu contains all HeaderItems from the TableWidget with the possibility to check/uncheck this columns.

- disableColumnForSelection: hide this column in the selection menu
- getCurrentVisibleColumns: return all visible items to store this information eg. in settings
- setColumnHidden: manually hide/show a column, eg. after restore from settings

### Usage

Copy the `QExtendedTableWidget` subdirectory into your project folder and add this to your qmake project file:

```cmake
include(QExtendedTableWidget/QExtendedTableWidget.pri)
```

### Example

![screenshot](screenshot/example_screenshot.gif)
