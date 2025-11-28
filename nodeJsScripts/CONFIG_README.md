# OCR Configuration Setup

## Setup Instructions

1. Copy `config.json` to `config.local.json`
2. Replace the placeholder API keys in `config.local.json` with your actual keys:
   - `your_perplexity_api_key_here` → Your Perplexity AI API key
   - `your_google_gemini_api_key_here` → Your Google Gemini API key

## API Keys Required

- **Perplexity AI**: For OCR text extraction
- **Google Gemini**: For Arabic to English translation

## Files

- `config.json` - Template with placeholder keys (safe to commit)
- `config.local.json` - Your local config with real keys (ignored by git)
- `config.template.json` - Backup template

## Security

- Never commit real API keys to the repository
- `config.local.json` is in .gitignore to prevent accidental commits
- Use placeholder values in the main config.json template