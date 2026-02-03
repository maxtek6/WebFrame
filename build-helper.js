#!/usr/bin/env node
const { execSync } = require('child_process');
const fs = require('fs');
const path = require('path');

try {
  const buildDir = path.join(__dirname, 'build');
  if (!fs.existsSync(buildDir)) {
    fs.mkdirSync(buildDir, { recursive: true });
  }

  console.log('📦 Configuring WebFrame with CMake...');
  execSync('cmake -B build -DCMAKE_BUILD_TYPE=Release', { stdio: 'inherit', cwd: __dirname });
  
  console.log('🔨 Building WebFrame...');
  execSync('cmake --build build --config Release', { stdio: 'inherit', cwd: __dirname });
  
  console.log('✓ WebFrame built successfully');
} catch (error) {
  console.error('✗ Build failed:', error.message);
  process.exit(1);
}
