# GUI TODO
- Move IVGA header to xvga_lib ... make separated implementations
## RESTRUCTURE Namespaces

rpgui::ui      -user accessible API for controls
rpgui::view
rpgui::layout
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