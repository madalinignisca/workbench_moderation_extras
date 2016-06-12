/**
* @file
* README file for Workbench Moderation Extras.
*/

Workbench Moderation Extras Module

/**
* @file
* README file for Workbench Notifier.
*/

Workbench Notifier Module

CONTENTS
--------

1.  Introduction
2.  Requirements
3.  Configuration

1.  Introduction
----------------

1.1  Concepts
-------------

Extends Workbench Moderation by adding email notifications to selected people
when specific transitions occur to content nodes.

2.  Requirements
----------------

Workbench Notifier requires:
- Workbench Moderation (and dependencies)
- Token (optional)

3.  Configuration
-----------------

- Download and install the module.
- Edit permission for roles allowed to 'moderate content
  from published to regular_review' and
  'Use "Regular review" workbench tab'
- Go to 'admin/config/workbench/extras' and enable node types,
  which users should receive notifications and in how many seconds to expire nodes

4.  TODO
----------------

- Allow admin to personalize the email template :) // would depend on token...
- Clean configuration on uninstall

