# GUI TODO
## RESTRUCTURE Namespaces

rpgui::control      -user accesible API for controls
rpgui::
rpgui::common   -base classes
rpgui::???      

rphid::mouse
rphid::kbd

ivga::color::   -colours 
ivga::          -functions

rplog::logger   -logger class


## Controls
- sprites/images
- line
- polyline
- ImageButton?
- RadioButton
- CheckBox
- Slider
- Stepper
- Switch
- Entry/editor
- ProgressBar
  
## Views
- CollerctionView
- StackLayout

## To add/implement
- Element Id, Parrent ?, 
- Visual element ? ... s

## Button xamarin example

Inheritance: Object -> BindableObject-> ELement -> NavigableElement -> VisualElement -> View -> Button

Implements: IBorderElement,  IButtonController,  IElementConfiguration,  IElementController,  IImageController,  IImageElement,  IFontElement,  IViewController,  IVisualElementController