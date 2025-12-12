import Jimp from 'jimp';
import QRCode from 'qrcode';
import fs from 'fs-extra';
import path from 'path';
import { fileURLToPath } from 'url';

// ES modules equivalent of __dirname
const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

class QRCodeAdder {
    constructor() {
        this.qrCodeSize = { width: 190, height: 178 }; // Fixed size as requested
    }

    /**
     * Generate QR code with fixed dimensions
     * @param {string} data - Data to encode in QR code
     */
    async generateQRCode(data) {
        try {
            // Generate QR code as buffer
            const qrBuffer = await QRCode.toBuffer(data, {
                width: this.qrCodeSize.width,
                margin: 2,
                color: {
                    dark: '#000000',
                    light: '#ffffff'
                }
            });

            // Create Jimp image from buffer
            const qrImage = await Jimp.read(qrBuffer);
            
            // Resize to exact dimensions
            qrImage.resize(this.qrCodeSize.width, this.qrCodeSize.height);

            return qrImage;
        } catch (error) {
            console.error('Error generating QR code:', error);
            throw error;
        }
    }

    /**
     * Add QR code to existing poster
     * @param {string} posterPath - Path to existing poster
     * @param {string} qrData - Data to encode in QR code
     * @param {string} outputPath - Path to save the new poster with QR code
     */
    async addQRToPoster(posterPath, qrData, outputPath) {
        try {
            console.log(`📖 Loading existing poster: ${posterPath}`);
            
            // Check if background image exists
            if (!await fs.pathExists(posterPath)) {
                throw new Error(`Background image not found: ${posterPath}`);
            }
            
            // Load existing poster
            const poster = await Jimp.read(posterPath);
            console.log(`📏 Poster dimensions: ${poster.getWidth()}x${poster.getHeight()}`);

            console.log('🔳 Generating QR code...');
            // Generate QR code
            const qrImage = await this.generateQRCode(qrData);

            // Use configurable position or default
            const qrPosition = this.qrPosition || { x: 417, y: 216 };
            
            console.log(`📌 Placing QR code at position: ${qrPosition.x}, ${qrPosition.y}`);
            console.log(`📐 QR code size: ${this.qrCodeSize.width}x${this.qrCodeSize.height}`);
            
            // Place QR code at the specified coordinates
            poster.composite(qrImage, qrPosition.x, qrPosition.y);

            console.log(`💾 Saving poster with QR code to: ${outputPath}`);
            console.log(`📍 Resolved path: ${path.resolve(outputPath)}`);
            
            // Save the result with absolute path to ensure proper location
            const absoluteOutputPath = path.resolve(outputPath);
            await poster.writeAsync(absoluteOutputPath);
            
            // Verify the file was actually written
            if (await fs.pathExists(absoluteOutputPath)) {
                console.log(`✅ Poster with QR code saved successfully!`);
                return absoluteOutputPath;
            } else {
                throw new Error(`Failed to save file to: ${absoluteOutputPath}`);
            }
        } catch (error) {
            console.error('❌ Error adding QR code to poster:', error);
            throw error;
        }
    }

    /**
     * Create QR data from activity information
     */
    createQRDataFromActivity(activityData) {
        // Return only the URL string, not a JSON object
        const registrationUrl = activityData.registrationUrl || `https://summerclub.com/register/${activityData.activityId}`;
        return registrationUrl;
    }

    /**
     * Main execution function with configurable parameters
     */
    static async execute() {
        console.log('📋 Command line arguments:', process.argv);
        console.log('📂 Current working directory:', process.cwd());
        
        // Check for command line arguments
        const customBgImage = process.argv[2];
        const customX = process.argv[3] ? parseInt(process.argv[3]) : null;
        const customY = process.argv[4] ? parseInt(process.argv[4]) : null;
        const customOutput = process.argv[5];
        
        // Use custom values or defaults
        const posterPath = customBgImage || 'Export/ActivtyPoster.png';
        const activityJsonPath = path.resolve(__dirname, 'sample_activity.json'); // Always use script directory
        const outputPath = customOutput || 'Export/final_poster.png';
        const qrPosition = {
            x: customX !== null ? customX : 417,
            y: customY !== null ? customY : 216
        };

        try {
            console.log('🚀 Starting QR code addition process...');
            console.log(`📖 Background image: ${posterPath}`);
            console.log(`📌 QR position: (${qrPosition.x}, ${qrPosition.y})`);
            console.log(`💾 Output: ${outputPath}`);
            
            // Load activity data
            const activityData = JSON.parse(await fs.readFile(activityJsonPath, 'utf8'));
            console.log(`📝 Loaded activity: ${activityData.title}`);
            
            const qrAdder = new QRCodeAdder();
            qrAdder.qrPosition = qrPosition; // Override default position
            const qrData = qrAdder.createQRDataFromActivity(activityData);
            
            console.log('🔗 QR Data to encode:', qrData);
            console.log('📊 QR Data type:', typeof qrData);
            console.log('📏 QR Data length:', qrData.length);
            
            // Ensure output directory exists - handle both relative and absolute paths
            const outputDir = path.dirname(outputPath);
            console.log(`📂 Ensuring directory exists: ${outputDir}`);
            await fs.ensureDir(outputDir);
            
            await qrAdder.addQRToPoster(posterPath, qrData, outputPath);
            
            // Verify file was created
            if (await fs.pathExists(outputPath)) {
                console.log(`✅ Success: QR code added to poster at position (${qrPosition.x}, ${qrPosition.y})`);
                console.log(`📄 Final poster saved as: ${outputPath}`);
                console.log(`📍 Full path: ${path.resolve(outputPath)}`);
            } else {
                throw new Error(`Output file was not created at: ${outputPath}`);
            }
            
        } catch (error) {
            console.error('❌ Error:', error.message);
            throw error;
        }
    }
}

// Auto-execute when script is run
if (process.argv[1] && process.argv[1].endsWith('qr_adder.js')) {
    QRCodeAdder.execute();
}

export default QRCodeAdder;