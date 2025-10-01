# devel branch
In this branch im trying out examples, expand them by custom code and try to understand how lvgl works more or less in detail.<br>
The following list is not in priority-order. The goals are just a brainstorming, what could be nice to have/has to be done. The goals can change over time and get vanished completely.

## developting goals
- **Custom Styles**: I want to create custom, more reduced styles for one or more screens, so that i just have to change something at one point, to change the look, eg via toggle button, to switch to another preset color. Corporate identity colors, colorblind-mode, etc.
- **Language**: I want to checkout if there are repos or LVGL implemented ways to have an easy way to switch between languages, without a huge development-effort.
- **Homebutton**: Setup an easy to implement "homebutton", that can be default on every screen. Maybe via style-setup or with custom-screen-XMLs. One or more predefined buttons.
- **Buttons With Images**: Try out, how images on Buttons work/are implemented.
- **Emulate And Test**: The biggest goal is implementing and testing the emulation tools provided by LVGL, to later have an easier transfer to onboard-UI-solutions. Onboard-testing will then be key-feature-tests and random tests, defined by corporate management (won't be public repo, when actual corporate property is used).
- **Button for Settings**: A button, which opens a small window for e.g. On/Off toggling, background has to still be visible, but a little bit opaque, so setting changes like color are visible to the user.
- **More**: Might add other stuff...

## development documentation
The different developed solutions will not have their own repos, but be available in the directories. The main function will have to be changed, to test every solution. If changes to the `CMakeLists.txt` or other files need to be done, I try to document it.

## current state
TBD