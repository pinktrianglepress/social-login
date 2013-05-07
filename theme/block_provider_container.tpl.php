<?php

/**
 * @file
 * Container in which the social network icons are displayed.
 */
global $base_url;
?>
<div class="oneall_social_login" style="margin:20px 0 10px 0">
 <div id="<?php echo filter_xss($containerid); ?>"><img src="<?php print $base_url.'/sites/all/themes/dailyxtra/images/sociallogin.png'; ?>"></div>
  <div id="top_user_info_bar">
   <?php
     if(user_is_logged_in()){
       global $user;
       print '| ';
       print '<span class="user-name">' . l($user->name, 'user') . '</span>';
       print ' | ';
       print '<span class="sign-out">' . l('Sign out', 'user/logout') . '</span>';
     }else{
       print '| ';
       print '<span class="register">' . l('Register', 'user/register') . '</span>';
       print ' | ';
       print '<span class="sign-in">' . l('Sign in', 'sign-in') . '</span>';
     }
   ?>
 </div>
</div>
