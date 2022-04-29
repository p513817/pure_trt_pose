import cv2, random

class DrawObjects(object):
    
    def __init__(self, topology, color=None, alpha=0.5, border=2):
        self.topology = topology
        self.colors=[ (random.randint(0,255), random.randint(0,255), random.randint(0,255)) for _ in range((topology.shape[0]+1)) ] if color==None else color
        self.alpha = alpha		
        self.border = border

    def __call__(self, image, object_counts, objects, normalized_peaks, palette=None):
        topology = self.topology
        palette = self.colors if (palette == None or len(palette)<len(self.colors) ) else palette

        height = image.shape[0]
        width = image.shape[1]

        image_org, image_draw = image.copy(), image.copy()

        K = topology.shape[0]
        count = int(object_counts[0])
        
        for i in range(count):
            
            obj = objects[0][i]
            
            C = obj.shape[0]

            for k in range(K):
                c_a = topology[k][2]
                c_b = topology[k][3]
                if obj[c_a] >= 0 and obj[c_b] >= 0:
                    peak0 = normalized_peaks[0][c_a][obj[c_a]]
                    peak1 = normalized_peaks[0][c_b][obj[c_b]]
                    x0 = round(float(peak0[1]) * width)
                    y0 = round(float(peak0[0]) * height)
                    x1 = round(float(peak1[1]) * width)
                    y1 = round(float(peak1[0]) * height)
                    cv2.line(image_draw, (x0, y0), (x1, y1), palette[k], self.border)

            for j in range(C):
                k = int(obj[j])
                if k >= 0:
                    peak = normalized_peaks[0][j][k]
                    x = round(float(peak[1]) * width)
                    y = round(float(peak[0]) * height)
                    cv2.circle(image_draw, (x, y), 3, palette[j], self.border)

        image_draw = cv2.addWeighted(image_org, self.alpha, image_draw, 1 - self.alpha, 0)

        return image_draw