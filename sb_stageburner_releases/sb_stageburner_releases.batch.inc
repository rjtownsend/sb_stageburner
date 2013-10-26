<?php

/**
 * Batch operation for cloning a repository.
 */
function sb_stageburner_releases_clone_repo($site_name, $repo_name, $repo_path, $tag_or_branch, &$context) {
  $git = variable_get('sb_stageburner_git_bin', '');
  $tag_or_branch = empty($tag_or_branch) ? 'master' : $tag_or_branch;

  // Change to the appropriate directory for the stageburner repo.
  _sb_stageburner_releases_batch_chdir($site_name, $repo_name);

  // If the repo already exists, fetch from origin, otherwise clone it.
  if (is_dir('.git')) {
    _sb_stageburner_exec($git . ' fetch origin', t('The !repo repository could not be updated.', array('!repo' => $repo_name)));
  }
  else {
    _sb_stageburner_exec($git .' clone ' . $repo_path . ' ./', t('The !repo repository could not be cloned.', array('!repo' => $repo_name)));
  }

  // Checkout the correct tag or branch.
  _sb_stageburner_exec($git . ' checkout -f ' . $tag_or_branch, t('The repo could not be checked out'));

  // If this is a branch, merge from origin into this branch.
  if(!_sb_stageburner_tag_exists($tag_or_branch)) {
    _sb_stageburner_exec($git . ' merge origin/' . $tag_or_branch, t('The repo could not be merged'));
  }

  // Update the batch context.
  $context['results'][] = t('Checked out the !repo repository. !tag_or_branch', array('!tag_or_branch' => '(' . $tag_or_branch . ')', '!repo' => $repo_name));
  $context['message'] = t('Checked out the !repo repository. !tag_or_branch', array('!tag_or_branch' => '(' . $tag_or_branch . ')', '!repo' => $repo_name));
}

/**
 * Batch operation for deleting all build files.
 */
function sb_stageburner_releases_clear_files() {
  $files = _sb_stageburner_releases_path();
  _sb_stageburner_exec('rm -rf ' . $files);
}

/**
 * Build batch complete callback function.
 */
function sb_stageburner_releases_build_batch_complete($success, $results, $operations) {
  if ($success) {
    drupal_set_message(t('The release has been successfully built.'));
  }
  else {
    drupal_set_message(t('The release failed.'), 'error');
  }
  // @TODO this is wrong in so many ways
  drupal_goto('deploy-site');
}

/**
 * Clear batch complete callback function.
 */
function sb_stageburner_releases_clear_batch_complete($success, $results, $operations) {
  if ($success) {
    drupal_set_message(t('All build files have been deleted. This will make the next release build take longer but it will not effect any sites on any environments.'));
  }
  else {
    drupal_set_message(t('The build files could not be deleted.'), 'error');
  }
}

/**
 * Helper funcion that returns the correct files path here all the git clones
 * should live for the various release operations.
 *
 * @return string
 *   path to sb_stageburner_releases in the private files directory.
 */
function _sb_stageburner_releases_path() {
  // @TODO /sb_releases/ should be the name of the project repo
  return _sb_stageburner_get_private_files_path() . '/sb_releases/';
}

/**
 * Helper function for changing directory on the command line. If the directory
 * does not exist, it will be created.
 *
 * @param sting $site_name
 *   The short name of the site.
 *
 * @param string $path
 *   The path relative to files/sb_stageburner_releases/site_name/
 *
 * @return string
 *   The curent working directory.
 */
function _sb_stageburner_releases_batch_chdir($site_name, $path) {
  // Create the releases directory in the files directory.
  $files = _sb_stageburner_releases_path() . $site_name . '/';
  $full_path = $files . $path;

  return _sb_stageburner_chdir($full_path);
}
