import globals from "globals";
import pluginJs from "@eslint/js";

export default [
  {
    files: ["src/js/*.js"],
    languageOptions: { sourceType: "commonjs" },
    rules: {
      /* Prefer === to == and !== to !=, but only warn */
      eqeqeq: "warn",
      /* Prefer ; use, but only warn (prettier will fix) */
      semi: "warn",
      /* Allow console.*() */
      "no-console": "off",
      /* Allow debugger; */
      "no-debugger": "off",
      /* Warn when using blocking alert, prompt, etc, but allow */
      "no-alert": "warn",
      /* Warn when using an unnecessary } else { after a return */
      "no-else-return": "warn",
      /* Ignore variables not declared at top of scope */
      "vars-on-top": "off"
    }
  },
  { languageOptions: { globals: globals.browser } },
  pluginJs.configs.recommended
];
