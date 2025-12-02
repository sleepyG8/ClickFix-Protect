# ClickFix-Protect
A POC of defending your system and Users from the popular ClickFix attack

If you are an admin of a company and are worried about trusting your users in the hands of modern day 
click-fix attacks?

Recently, I was reading some data that stated almost %50 percent of cyber attacks in 2025 were from 
a website telling a user to select Windows + R and then CTRL+V to copy a powershell command into 
RUN.

This has posed as a significant threat from the average joe, all the way up to corprate businesses person.

So, Ive created a utility to monitor the clipboard and print to the console if a string from the config file
is found inside of it. Obviously, we as a community need to populate the file with common click-fix powershell
commands found in the wild.

