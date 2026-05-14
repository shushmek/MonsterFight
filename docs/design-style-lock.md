# MonsterFight UI Style Lock

## Project Visual Genre
SFML fantasy combat demo with image-led full-screen scenes and large sprite buttons.

## Source References Used
- `Engine.h`
- `Engine.cpp`
- `Sprite/MainMenu.jpg`
- `Sprite/GameBackground.jpg`
- `Sprite/btn.png`
- `Font/BankGothic.otf`

## Layout Grammar
- Keep the fixed `1280x720` scene layout.
- Use full-screen background art as the primary surface.
- Place controls directly over the scene, aligned in simple vertical stacks.
- Do not introduce floating panels for simple navigation.

## Spacing Rhythm
- Use large vertical button spacing similar to the current menu.
- Keep menu controls near the left side.
- Keep in-game utility controls compact and near the upper-left corner.

## Typography System
- Use `Font/BankGothic.otf` for game UI text.
- Use uppercase labels for primary buttons and screen headings.
- Keep text sizes close to existing button sizes: large for menu actions, smaller for dense screen text.

## Color / Token System
- Preserve existing button colors: purple `Color(180, 86, 140)` for normal actions and red `Color(222, 32, 32)` for exit/back actions.
- Use white UI text over dark/full-screen art.
- Use the existing red HP bar color.

## Surface Treatment
- Background images are the main visual surface.
- Text overlays may use simple dark translucent rectangles only for readability.
- Avoid decorative surfaces that compete with sprite art.

## Border / Radius / Shadow Rules
- No rounded card containers.
- No shadows beyond what is already baked into sprites/assets.
- Reuse `Sprite/btn.png` instead of drawing new button shapes.

## Component Grammar
- Buttons should be instances of the existing `Button` class.
- Health display should continue using the existing `Slider`.
- New text screens should use simple SFML `Text` rows.

## Interaction And Motion Style
- Keep interactions simple: mouse buttons and direct keyboard shortcuts.
- Reuse existing scene switching rather than adding modal overlays.

## Content Hierarchy Rules
- Headings are large uppercase text.
- Data rows are compact, left-aligned, and grouped by spacing.
- Logs show newest recent entries without complex filtering.

## Responsive Behavior Rules
- No responsive behavior is currently present; preserve fixed layout.

## Must-Preserve Traits
- Full-screen art background.
- Existing button sprite.
- Existing BankGothic font.
- Direct scene switching.
- Compact in-game controls.

## Forbidden Traits
- Glassmorphism.
- Blur/translucent panels as a visual style.
- Floating card stacks.
- Oversized rounded containers.
- Dashboard-card mosaics.
- Heavy decorative gradients.
- Ornamental icons.
- Parallel component systems.
- New tokens when equivalent existing colors/assets already exist.

## Litmus Tests
- The new buttons should look like the original menu buttons.
- The statistics and logs screens should feel like simple game screens, not a modern dashboard.
- The game should remain usable at the current `1280x720` size without new assets.

## File / Component Evidence
- `Engine.h`: existing fixed scene layout and buttons.
- `Button.cpp`: sprite-backed text buttons.
- `Slider.cpp`: existing HP bar treatment.
