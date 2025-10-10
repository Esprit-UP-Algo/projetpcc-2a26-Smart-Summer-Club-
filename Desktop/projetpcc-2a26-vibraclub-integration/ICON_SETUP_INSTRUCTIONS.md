# PNG Icon Setup Instructions

## How to Add Your PNG Icons

1. **Place your PNG icon files in the `icons` folder with these exact names:**
   - `employees.png` - for the Employees button (navButton)
   - `members.png` - for the Members button (navButton1)
   - `equipment.png` - for the Equipment button (navButton2)
   - `activities.png` - for the Activities button (navButton3)
   - `payments.png` - for the Payments button (navButton4)
   - `search.png` - for Search button (actionButton)
   - `upload.png` - for Upload/Choose File button (actionButton1)
   - `confirm.png` - for Confirm/Add button (actionButton2)
   - `edit.png` - for Edit/Update button (actionButton3)

2. **Add icons to resources.qrc file:**
   After adding PNG files, update your `resources.qrc` file to include:
   ```xml
   <RCC>
     <qresource prefix="/icons">
       <file>icons/employees.png</file>
       <file>icons/members.png</file>
       <file>icons/equipment.png</file>
       <file>icons/activities.png</file>
       <file>icons/payments.png</file>
       <file>icons/search.png</file>
       <file>icons/upload.png</file>
       <file>icons/confirm.png</file>
       <file>icons/edit.png</file>
     </qresource>
   </RCC>
   ```

3. **Uncomment the icon code:**
   In `employeradmin.cpp`, uncomment the code inside the `setupIcons()` function.

4. **Icon Requirements:**
   - Format: PNG (recommended)
   - Size: 24x24 pixels (or any square size - they will be scaled)
   - Background: Transparent (recommended)
   - Color: Any color that matches your UI theme

5. **Where to get icons:**
   - **Free sources:** 
     - Feather Icons (https://feathericons.com/)
     - Heroicons (https://heroicons.com/)
     - Lucide (https://lucide.dev/)
     - Material Design Icons (https://fonts.google.com/icons)
   - **Paid sources:**
     - Iconfinder (https://www.iconfinder.com/)
     - Icons8 (https://icons8.com/)

6. **After adding icons:**
   - Clean and rebuild your project
   - The icons will automatically appear next to the button text

## Customization Options

You can modify the `setupIcons()` function in `employeradmin.cpp` to:
- Change icon size: Modify `QSize iconSize(24, 24);`
- Change icon position: Use different `Qt::ToolButtonStyle` values:
  - `Qt::ToolButtonTextBesideIcon` - Text beside icon
  - `Qt::ToolButtonTextUnderIcon` - Text under icon
  - `Qt::ToolButtonIconOnly` - Icon only
  - `Qt::ToolButtonTextOnly` - Text only

## Example Icon Names Mapping
- 👥 employees.png → Users/People icon
- 👤 members.png → Single person icon
- 🏋️ equipment.png → Dumbbell/Gym equipment icon
- 🏃 activities.png → Running/Activity icon
- 💳 payments.png → Credit card/Payment icon
- 🔍 search.png → Magnifying glass icon
- 📁 upload.png → Folder/Upload icon
- ✅ confirm.png → Checkmark icon
- ✏️ edit.png → Pencil/Edit icon