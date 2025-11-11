% png_compare_plot.m
% Compares two PNGs and shows differing pixels in red.

% --- Config ---
file1 = 'C:/northh/repos/lvgl_vscode/bin/screenshots/screentest_9.png';
file2 = 'C:/northh/repos/lvgl_vscode/bin/screenshots/screentest_9_err.png';
threshold = 1; % tolerance (0–255)

% --- Read ---
img1 = imread(file1);
img2 = imread(file2);

% --- Convert grayscale or indexed to RGB ---
if size(img1,3) == 1
    img1 = repmat(img1, [1 1 3]);
end
if size(img2,3) == 1
    img2 = repmat(img2, [1 1 3]);
end

if ~isequal(size(img1), size(img2))
    error('Images must have identical dimensions.');
end

% --- Compute difference ---
absDiff = abs(double(img1) - double(img2));
diffMask = any(absDiff > threshold, 3);

% --- Prepare red overlay ---
overlay = im2double(img1);
redOverlay = overlay;
redOverlay(:,:,1) = max(redOverlay(:,:,1), double(diffMask)); % add red where difference
redOverlay(:,:,2) = redOverlay(:,:,2) .* ~diffMask;
redOverlay(:,:,3) = redOverlay(:,:,3) .* ~diffMask;

% --- Show overlay ---
figure('Name','Differences highlighted in red');
imshow(redOverlay);
title(sprintf('Differences highlighted (threshold = %d)', threshold));

% % --- Show only differing pixels (red on black) ---
% diffOnly = zeros(size(overlay));
% diffOnly(:,:,1) = double(diffMask);
% figure('Name','Only differing pixels (red)');
% imshow(diffOnly);
% title('Only differing pixels (red)');
% 
% % --- Show coordinate plot ---
% [rows, cols] = find(diffMask);
% figure('Name','Coordinates of differing pixels');
% imshow(img1);
% hold on;
% plot(cols, rows, '.', 'Color', [1 0 0], 'MarkerSize', 1);
% title(sprintf('Differing pixel coordinates (count = %d)', numel(rows)));
% hold off;
