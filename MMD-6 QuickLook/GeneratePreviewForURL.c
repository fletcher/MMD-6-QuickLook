#include <CoreFoundation/CoreFoundation.h>
#include <CoreServices/CoreServices.h>
#include <QuickLook/QuickLook.h>


#include <libMultiMarkdown/libMultiMarkdown.h>
#include <libMultiMarkdown/d_string.h>
#include <libMultiMarkdown/token.h>

#include <libgen.h>


OSStatus GeneratePreviewForURL(void *thisInterface, QLPreviewRequestRef preview, CFURLRef url, CFStringRef contentTypeUTI, CFDictionaryRef options);
void CancelPreviewGeneration(void *thisInterface, QLPreviewRequestRef preview);

/* -----------------------------------------------------------------------------
   Generate a preview for file

   This function's job is to create preview for designated file
   ----------------------------------------------------------------------------- */

int cfurltochar (CFURLRef url, char * buffer, int len) {
	if (url == NULL) {
		fprintf(stderr, "null URL\n");
		return -1;
	}

	if (!CFURLGetFileSystemRepresentation(url, true, (uint8 *) buffer, len)) {
		fprintf(stderr, "error converting URL\n");
		return -1;
	}

	return 0;
}


OSStatus GeneratePreviewForURL(void *thisInterface, QLPreviewRequestRef preview, CFURLRef url, CFStringRef contentTypeUTI, CFDictionaryRef options)
{
	char buffer[2048];	// Path to file

	if (cfurltochar(url, buffer, 2048)) {
		return -1;
	}

#ifdef kUseObjectPool
	token_pool_init();
#endif

	DString * fileBuffer = scan_file(buffer);
	char * folder = dirname(buffer);

	mmd_prepend_mmd_header(fileBuffer);
	mmd_append_mmd_footer(fileBuffer);

	DString * result;
	result = mmd_d_string_convert_to_data(fileBuffer, EXT_COMPLETE | EXT_SMART | EXT_NOTES | EXT_CRITIC, FORMAT_HTML, 0, folder);

#ifdef kUseObjectPool
	token_pool_drain();
	token_pool_free();
#endif

	CFDataRef data = CFDataCreateWithBytesNoCopy(kCFAllocatorDefault, (const uint8 *)result->str, result->currentStringLength, kCFAllocatorNull);
	CFDictionaryRef properties = CFDictionaryCreate(NULL, NULL, NULL, 0, NULL, NULL);

	QLPreviewRequestSetDataRepresentation(preview, data, kUTTypeHTML, properties);

	d_string_free(fileBuffer, true);
	d_string_free(result, true);

	return noErr;
}

void CancelPreviewGeneration(void *thisInterface, QLPreviewRequestRef preview)
{
    // Implement only if supported
}
