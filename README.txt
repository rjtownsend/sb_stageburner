sb_stageburner is a proof-of-concept that integrates Drupal with Github's
API, allowing administrators to associate a node with a repository and
then do checkouts of forks/branches/tags of that repo. It's entirely
experimental code and does nothing more than checkout code to the 
private files directory. You may find this code interesting if you are 
attempting to do the same. I plan no further work on this.

The following modules are included:

  sb_stageburner
  ==============
  Mostly helper functions for command line operations and working with
  Github's API. 

  sb_stageburner_releases
  =======================
  Sets up the ctools modal/UI to search for forks/branches/tags and triggers
  a batch operation to checkout to private files directory.

  sb_config
  =========
  A feature with content types, fields, configuration settings, etc. 

Installation
============
  1. Install and enable module, including dependencies. See 
     http://drupal.org/documentation/install/modules-themes/modules-7
     for details
  2. Navigate to /admin/stageburner/config and enter required info.
  3. Create a couple project nodes at /node/add/project
  4. Navigate to /deploy-site and click on project to checkout repo
     to private files directory

