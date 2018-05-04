MultiMarkdown 6 QuickLook Generator  
Copyright 2018 Fletcher Penney for MultiMarkdown Software, LLC  
2018-05-04 


This is a simple framework for a QuickLook Generator based on MultiMarkdown version 6.


The QuickLook code is given to the public domain (e.g. `GeneratePreviewForURL.c`).  MultiMarkdown itself is MIT licensed and is a separate project.


To compile:

1. Clone this repository (e.g. `git clone `)

2. Clone MultiMarkdown submodule:

		./link_git_modules

3. Make MultiMarkdown Xcode project:

		cd submodules/mmd6
		make xcode

4. Open `MMD-6 QuickLook.xcodeproj`

5. Disable `libCurl` in `libMultiMarkdown`

	* In the `MultiMarkdown.xcodeproj` project, modify the "Build Settings" for `libMultiMarkdown`.  Under "Preprocessed Macros", delete the `USE_CURL` line for each build type.

* Under "Build Phases" for `libMultiMarkdown`, change the "Copy Files" destination to "Products Directory" instead of "Executables".

6. Build the project and install where desired (e.g. `~/Library/QuickLook`).