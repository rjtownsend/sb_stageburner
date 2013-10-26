<?php

/**
 * Form builder for the admin function.
 */
function sb_stageburner_admin_settings() {
  $form['settings'] = array(
    '#type' => 'vertical_tabs',
  );

  // Default tag settings.
  $form['sb_stageburner_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('StageBurner Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#group' => 'settings',
  );
  $form['sb_stageburner_settings']['sb_stageburner_git_bin'] = array(
    '#type' => 'textfield',
    '#title' => t('Server path to the git binary'),
    '#description' => t('The location of the git bin. Ex. /usr/local/bin/git'),
    '#default_value' => variable_get('sb_stageburner_git_bin', ''),
  );
  $form['sb_stageburner_settings']['sb_stageburner_drush_bin'] = array(
    '#type' => 'textfield',
    '#title' => t('Server path to the drush binary'),
    '#description' => t('The location of the drush bin. Ex. /usr/local/bin/drush'),
    '#default_value' => variable_get('sb_stageburner_drush_bin', ''),
  );
  $form['sb_stageburner_settings']['sb_stageburner_github_org_name'] = array(
    '#type' => 'textfield',
    '#title' => t('DEPRECATED GitHub Orginization Name'),
    '#description' => t('Enter the username on GitHub that owns main repositories.'),
    '#default_value' => variable_get('sb_stageburner_github_org_name', ''),
  );
  $form['sb_stageburner_settings']['sb_stageburner_github_sb_repo_name'] = array(
    '#type' => 'textfield',
    '#title' => t('DEPRECATED GitHub StateBurner Core Repository Name'),
    '#description' => t('Enter repository name on GitHub.'),
    '#default_value' => variable_get('sb_stageburner_github_sb_repo_name', ''),
  );
  $form['sb_stageburner_settings']['sb_github_credentials'] = array(
    '#type' => 'textfield',
    '#title' => t('Stageburner GitHub Credentials'),
    '#description' => t('Enter the name and password used to authenticate with Github'),
    '#default_value' => variable_get('sb_github_credentials', ''),
  );

  $form['sb_stageburner_advanced_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#group' => 'settings',
  );
  $form['sb_stageburner_advanced_settings']['sb_stageburner_debug_mode'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable debug mode.'),
    '#description' => t('Display debugging messages when running utilities.'),
    '#default_value' => variable_get('sb_stageburner_debug_mode', '0'),
  );

  return system_settings_form($form);
}
